import pandas as pd
import matplotlib.pyplot as plt

# 讀取 CSV 檔案
filename = "simData/Apogee-200-13s-TestResult.csv"  # <- 這邊改成你的檔名
df = pd.read_csv(filename)

# 提取欄位
time = df["Time"]
alt = df["Alt"]

# 繪製 Alt 對 Time 的圖
plt.figure(figsize=(10, 6))
plt.plot(time, alt, label="Altitude", color="#1f318f")  # ← 這邊可以改顏色，例如 "red", "#33cc33"

# 找出 Chu1, Chu2, Chu3 從 0 變成 1 的時間點
for col, color, label in [("Chu1", "red", "Chu1 Trigger"),
                          ("Chu2", "orange", "Chu2 Trigger"),
                          ("Chu3", "green", "Chu3 Trigger")]:
    trigger_indices = df.index[(df[col].shift(1, fill_value=0) == 0) & (df[col] == 1)]
    for idx in trigger_indices:
        t_trigger = df.loc[idx, "Time"]
        plt.axvline(x=t_trigger, color=color, linestyle="--", label=label)

# 圖表格式設定
plt.xlabel("Time (s)")
plt.ylabel("Altitude")
plt.title("Simulate 4 Altitude vs Time")
plt.legend()
plt.grid(True)

# 儲存圖片
plt.savefig("simData/Apogee-200-13s.png", dpi=300)
# plt.show()
