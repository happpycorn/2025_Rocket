import os
import pandas as pd
import numpy as np

FOLDER_PATH = "Program/Sim_Data"
FILE_PATTERN = "{}_{}.csv"

max_altitudes = []

title = "Altitude (m)"  # 高度欄位名稱

# 加入 0_0.csv
filename = os.path.join(FOLDER_PATH, FILE_PATTERN.format(0, 0))
df = pd.read_csv(filename)
if title in df.columns:
    max_altitudes.append(df[title].max())

# 加入其他資料
for i in range(8):
    for j in [2, 4]:
        filename = os.path.join(FOLDER_PATH, FILE_PATTERN.format(i, j))
        if not os.path.exists(filename):
            continue
        try:
            df = pd.read_csv(filename)
            if title in df.columns:
                max_altitudes.append(df[title].max())
        except Exception as e:
            print(f"Read error {filename}: {e}")

# 計算平均與標準差
mean_altitude = np.mean(max_altitudes)
std_altitude = np.std(max_altitudes, ddof=1)

# 印出結果
print(f"Average Max Altitude: {mean_altitude:.3f} m")
print(f"Standard Deviation:   {std_altitude:.3f} m")
