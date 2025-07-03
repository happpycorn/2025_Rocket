import pandas as pd
import matplotlib.pyplot as plt

# 這裡改成你的 CSV 檔名
csv_path = 'Program/Sim_Data/0_0.csv'
output_image_name = "rocket_flight_data_CPCG.png"

cp_color = '#1F318F'
cg_color = '#E9DC01'
stability_color = '#019A7B'

# 讀取 CSV
df = pd.read_csv(csv_path)

# 確認欄位名稱
time = df['# Time (s)']
cp_col = 'CP location (mm)'
cg_col = 'CG location (mm)'
stability_col = 'Stability margin calibers (​)'

plt.figure(figsize=(10,6))

# 建立主軸 ax1
ax1 = plt.gca()
ax2 = ax1.twinx()  # 建立第二條 y 軸

# CP 和 CG 用同一個 y 軸 (ax1)
ax1.plot(time, df[cp_col], label='CP location (mm)', color=cp_color, linewidth=2.5)
ax1.plot(time, df[cg_col], label='CG location (mm)', color=cg_color, linewidth=2.5)
ax1.set_ylabel('Location (mm)')
ax1.legend(loc='upper left')
ax1.set_xlabel('Time (s)')

# Stability margin 用第二條 y 軸 (ax2)
ax2.plot(time, df[stability_col], label='Stability margin calibers', color=stability_color, linewidth=2.5)
ax2.set_ylabel('Stability margin calibers')
ax2.legend(loc='upper right')

plt.xlabel('Index')
plt.title('CP, CG Location and Stability Margin')
ax1.grid(True)
plt.tight_layout()

plt.savefig(output_image_name, dpi=500)

plt.show()
