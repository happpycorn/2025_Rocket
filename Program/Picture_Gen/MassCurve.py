import pandas as pd
import matplotlib.pyplot as plt
from scipy.ndimage import gaussian_filter1d

# === 參數設定 ===
csv_file = 'Data/masscurve-Output_CSV.csv'  # ← 你的檔案名
color = '#019A7B'         # ← 可以改成 red, green, black, #RRGGBB 等
smooth_sigma = 1       # ← 平滑程度，數字越大越平滑

output_image_name = "rocket_flight_data_Mass_Curve.png"

# === 讀取 CSV 檔案 ===
df = pd.read_csv(csv_file)

# === 取出資料列 ===
positions = df['position(mm)']
mass = df['mass(g/mm)']

# === 平滑化資料 ===
smoothed_mass = gaussian_filter1d(mass, sigma=smooth_sigma)

# === 畫圖 ===
plt.figure(figsize=(10, 6))
plt.plot(positions, smoothed_mass, color=color, linewidth=2, label='Smoothed Mass')
# plt.scatter(positions, mass, color='gray', alpha=0.5, label='Raw Data')  # 原始資料點
plt.xlabel('Position (mm)')
plt.ylabel('Mass (g/mm)')
plt.title('Mass Distribution')
plt.legend()
plt.grid(True)
plt.tight_layout()

plt.savefig(output_image_name)

plt.show()
