import os
import csv
import matplotlib.pyplot as plt

CATCH_VALUE = ["Position East of launch (m)", "Position North of launch (m)"]
FOLDER_PATH = "Program/Land_Point_Sim/Data"
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
plt.figure(figsize=(10, 6))
plt.scatter(0, 0, color='black', marker='x', s=100, label='Launch Point')

for j in range(3):
    x_vals = [float(xy[0]) for xy in xy_lists[j]]
    y_vals = [float(xy[1]) for xy in xy_lists[j]]
    plt.scatter(x_vals, y_vals, label=labels[j], color=colors[j], marker='o')

plt.xlabel(CATCH_VALUE[0])
plt.ylabel(CATCH_VALUE[1])
plt.xlim(-100, 1000)
plt.ylim(-300, 300)
plt.title("Landing point prediction map")
plt.legend()
plt.grid(True, color='gray', linestyle='--', linewidth=0.5, alpha=0.3)
plt.tight_layout()
plt.savefig(output_image_name, dpi=300, bbox_inches='tight')
plt.show()