import os
import csv
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# === 參數設定 ===
FOLDER_PATH = "Program/Sim_Data"
FILE_PATTERN = "{}_{}.csv"           # 檔名格式，例如 0_0.csv、1_0.csv
FILE_COUNT = 8                      # 要讀幾張檔案（例如 0~4）
COLOR_LIST = ['#F20028', '#1F318F', '#019A7B']
X_COL = "Position East of launch (m)"
Y_COL = "Position North of launch (m)"
Z_COL = "Altitude (m)"
output_image_name = "3D_Trajectory.png"

def read_xyz_from_csv(filename, x_col, y_col, z_col):
    x_list, y_list, z_list = [], [], []
    try:
        with open(filename, newline='', encoding='utf-8') as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                try:
                    x_list.append(float(row[x_col]))
                    y_list.append(float(row[y_col]))
                    z_list.append(float(row[z_col]))
                except (KeyError, ValueError):
                    continue
    except FileNotFoundError:
        print(f"⚠️ 找不到檔案：{filename}")
    return x_list, y_list, z_list

# === 畫圖 ===
fig = plt.figure(figsize=(10, 8))
ax = fig.add_subplot(111, projection='3d')

for i in range(FILE_COUNT):
    for j in [2, 4, 6]:
        filename = os.path.join(FOLDER_PATH, FILE_PATTERN.format(i, j))
        x, y, z = read_xyz_from_csv(filename, X_COL, Y_COL, Z_COL)
        if not x:
            continue  # 略過空資料

        color = COLOR_LIST[j % len(COLOR_LIST)]
        ax.plot(x, y, z, color=color, marker='o', markersize=3)

        # 起點與終點標記
        ax.scatter(x[0], y[0], z[0], color=color, s=50, marker='s')  # 起點
        ax.scatter(x[-1], y[-1], z[-1], color=color, s=50, marker='^')  # 終點

# === 圖表設計 ===
ax.set_xlabel('X (East of launch) [m]')
ax.set_ylabel('Y (North of launch) [m]')
ax.set_zlabel('Z (Altitude) [m]')
ax.set_title('3D Flight Trajectories')
ax.legend()
ax.grid(True)
ax.set_xlim(-100, 1000)
ax.set_ylim(-300, 300)
ax.set_zlim(0, 1200)

plt.tight_layout()
plt.savefig(output_image_name, dpi=300)
plt.show()
