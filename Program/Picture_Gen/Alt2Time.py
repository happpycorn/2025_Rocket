import pandas as pd
import matplotlib.pyplot as plt

# 載入 CSV 檔案
df = pd.read_csv('Data/RocketSim-WS0.csv')  # <- 改成你的檔名

output_image_name = "rocket_flight_data_alt_ver_acc_vs_t.png"

# 提取欄位
time = df['Time (s)']
altitude = df['Altitude (m)']
velocity = df['Vertical velocity (m/s)']
acceleration = df['Vertical acceleration (m/s²)']

# 自訂顏色（你可以改這裡）
color_altitude = '#019A7B'
color_velocity = '#1F318F'
color_acceleration = '#E9DC01'

# 繪圖開始
fig, ax1 = plt.subplots(figsize=(10, 6))

# 右邊 Y 軸：速度與加速度
ax2 = ax1.twinx()
ax2.set_ylabel('Velocity / Acceleration', color='gray')
ax2.plot(time, acceleration, color=color_acceleration, label='Vertical Acceleration', linewidth=2.5, zorder=1)
ax2.plot(time, velocity, color=color_velocity, linestyle='--', label='Vertical Velocity', linewidth=2.5, zorder=2)
ax2.tick_params(axis='y', labelcolor='gray')
ax2.set_ylim(-50, 200)  # ✅ 右側 Y 軸範圍（這裡設定為 -50 到 50）

# 左邊 Y 軸：高度
ax1.set_xlabel('Time (s)')
ax1.set_ylabel('Altitude (m)', color=color_altitude)
ax1.plot(time, altitude, color=color_altitude, label='Altitude', linewidth=2.5, zorder=3)
ax1.tick_params(axis='y', labelcolor=color_altitude)
ax1.set_ylim(-300, 1200)  # ✅ 左側 Y 軸高度範圍（這裡設定為 0 到 1500）

# 合併圖例
lines1, labels1 = ax1.get_legend_handles_labels()
lines2, labels2 = ax2.get_legend_handles_labels()
ax1.legend(lines1 + lines2, labels2 + labels1 , loc='upper right')

plt.title('Flight Data: Altitude, Velocity, and Acceleration vs Time')
plt.grid(True)
plt.tight_layout()

plt.savefig(output_image_name)

plt.show()
