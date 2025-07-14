import os
import pandas as pd
import matplotlib.pyplot as plt
import seaborn as sns

FOLDER_PATH = "Program/Sim_Data"
FILE_PATTERN = "{}_{}.csv"
output_image_name = "landing_time.png"

# 儲存最後時間
final_times = []

# 先加入 0_0.csv
filename = os.path.join(FOLDER_PATH, FILE_PATTERN.format(0, 0))
df = pd.read_csv(filename)
if "# Time (s)" in df.columns:
    final_times.append(df["# Time (s)"].iloc[-1])

# 加入其他資料
for i in range(8):  # i = 0~7
    for j in [2, 4]:
        filename = os.path.join(FOLDER_PATH, FILE_PATTERN.format(i, j))
        if not os.path.exists(filename):
            continue
        try:
            df = pd.read_csv(filename)
            if "# Time (s)" in df.columns:
                final_times.append(df["# Time (s)"].iloc[-1])
        except Exception as e:
            print(f"Read error {filename}: {e}")

# === KDE 曲線圖 ===
plt.figure(figsize=(10, 6))
sns.kdeplot(final_times, fill=True, linewidth=2, color="#019a7b")

import numpy as np

# 計算平均與標準差
mean_time = np.mean(final_times)
std_time = np.std(final_times, ddof=1)  # sample standard deviation

print(f"Final Time Mean: {mean_time:.3f} s")
print(f"Final Time Std Dev: {std_time:.3f} s")

plt.xlabel("Final Time (s)")
plt.ylabel("Density")
plt.title("Distribution of Final Time")
plt.grid(True)
plt.tight_layout()
plt.savefig(output_image_name, dpi=500)
plt.show()
