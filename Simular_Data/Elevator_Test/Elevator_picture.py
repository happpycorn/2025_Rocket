import pandas as pd
import matplotlib.pyplot as plt

# 讀取 CSV 文件
df = pd.read_csv('Simular_Data\Elevator_Test\Elevator_Test_Data.csv')

# 提取時間和高度數據
time = df['Time']
height_1 = df['High_1']
height_2 = df['High_2']

# 設置畫圖
plt.figure(figsize=(10, 6))

# 畫出高度1的折線圖
plt.plot(time, height_1, label='Height 1', color='#019a7b', linewidth=2)

# 畫出高度2的折線圖
plt.plot(time, height_2, label='Height 2', color='#e9dc01', linewidth=2)

# 添加標題和標籤
plt.title('Height vs Time')
plt.xlabel('Time')
plt.ylabel('Height (m)')

# 顯示圖例
plt.legend()

# 顯示格線
plt.grid(True)

# 儲存圖像為 PNG 文件，高解析度
plt.tight_layout()
plt.savefig('height_vs_time.png', dpi=300)  # 300 DPI 提供高解析度
