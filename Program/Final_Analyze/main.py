import pandas as pd
import matplotlib.pyplot as plt

# === 參數設定區 ===
file_path = '/Users/corn/Documents/Program/2025_Rocket/Test_Record/Final/ground_data_all.csv'
x_col = 'Time'         # X 軸欄位
y1_col = 'Altitude'        # 左側 Y 軸
y2_col = 'Velocity'        # 右側 Y 軸
x_col = 'slope_data_0'         # X 軸欄位
y1_col = 'slope_data_1'        # 左側 Y 軸
y2_col = 'slope_data_2'        # 右側 Y 軸

output_image_name = "final_alt2time.png"

# 🎨 顏色設定（你只要改這裡）
color_y1 = '#1F318F'  # 藍色線（左）
color_y2 = '#019A7B'  # 紅色線（右）
vline_color = '#000000'  # 垂直線（綠）

# === 資料處理 ===
start_time = 3777989
df = pd.read_csv(file_path)
df[x_col] = (df[x_col] - start_time) / 1000

# === 繪圖 ===
fig, ax1 = plt.subplots()

# 左側 Y 軸線條
ax1.plot(df[x_col], df[y1_col], color=color_y1, label=y1_col)
ax1.set_xlabel(x_col)
ax1.set_ylabel(y1_col, color=color_y1)
ax1.tick_params(axis='y', labelcolor=color_y1)
ax1.set_ylim(-50, 200)

# 右側 Y 軸線條
# ax2 = ax1.twinx()
# ax2.plot(df[x_col], df[y2_col], color=color_y2, label=y2_col)
# ax2.set_ylabel(y2_col, color=color_y2)
# ax2.tick_params(axis='y', labelcolor=color_y2)
# ax2.set_ylim(-100, 500)

# # 加入垂直線
# ax1.axvline(x=(3782989 - start_time) / 1000, color=vline_color, linestyle='--', linewidth=1.5)

# 顯示標題和圖表
plt.title(f"{y1_col} and {y2_col} vs {x_col}")
plt.grid(True)
plt.savefig(output_image_name, dpi=300)
plt.show()
