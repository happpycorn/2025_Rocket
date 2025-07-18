import os
import csv
import matplotlib.pyplot as plt

CATCH_VALUE = ["Position East of launch (m)", "Position North of launch (m)"]
FOLDER_PATH = "Program/Sim_Data"
colors = ['#019A7B', '#1F318F', '#F20028']
labels = ['2 m/s', '4 m/s', '6 m/s']
output_image_name = "Landing_Point_Prediction_Map.png"

def get_last_row_values(filename, columns):
    with open(filename, newline='', encoding='utf-8') as csvfile:
        reader = csv.DictReader(csvfile)
        last_row = None
        for row in reader:
            last_row = row  # 每次迴圈都覆蓋，最後會是最後一行

        if last_row is None:
            raise ValueError("CSV 檔案是空的")

        return [last_row[col] for col in columns]

# === 資料容器 ===
xy_lists = [[] for _ in range(3)]  # 每組是 [(x, y), (x, y), ...]

# === 收集資料 ===
for i in range(8):
    for j, suffix in enumerate([2, 4, 6]):
        filename = os.path.join(FOLDER_PATH, f"{i}_{suffix}.csv")
        try:
            values = get_last_row_values(filename, CATCH_VALUE)
            xy_lists[j].append((values[0], values[1]))  # (x, y)
        except Exception as e:
            print(f"讀取失敗：{filename}，錯誤：{e}")

# === 繪圖 ===
plt.figure(figsize=(8, 6))
plt.scatter(0, 0, color='black', marker='x', s=100, label='Launch Point')

for j in range(3):
    x_vals = [float(xy[0]) for xy in xy_lists[j]]
    y_vals = [float(xy[1]) for xy in xy_lists[j]]
    plt.scatter(x_vals, y_vals, label=labels[j], color=colors[j], marker='o')

# === ABCDEFG 座標（以發射點為中心的 X, Y，單位：m）===
ab_points = {
    'A': (628.5, -599.0),
    'B': (271.5, -599.0),
    'C': (-55.0, -105.0),
    'D': (-55.0, 111.0),
    'E': (262.0, 545.5),
    'F': (628.5, 545.5),
    'G': (939.2, 18.5),
}

# === 畫出 ABCDEFG 點 ===
for name, (x, y) in ab_points.items():
    plt.scatter(x, y, color='orange', marker='s', s=60, edgecolors='black', zorder=5)
    plt.text(x + 10, y + 10, name, fontsize=9, color='black')

# === 畫出包住 ABCDEFG 的區域 ===
# 排序：照你的資料順序連起來會形成一個封閉區域
polygon_order = ['A', 'B', 'C', 'D', 'E', 'F', 'G']
polygon_coords = [ab_points[name] for name in polygon_order]

# 填色
x_polygon, y_polygon = zip(*polygon_coords)
plt.fill(x_polygon, y_polygon, color='orange', alpha=0.1, label='Landing Safety Zone')

plt.xlabel(CATCH_VALUE[0])
plt.ylabel(CATCH_VALUE[1])
plt.xlim(-200, 1300)
plt.ylim(-650, 600)
plt.title("Landing point prediction map")
plt.legend()
plt.grid(True, color='gray', linestyle='--', linewidth=0.5, alpha=0.3)
plt.tight_layout()
plt.savefig(output_image_name, dpi=300, bbox_inches='tight')
plt.show()