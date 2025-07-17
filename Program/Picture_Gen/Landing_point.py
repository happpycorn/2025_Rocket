import os
import pandas as pd
import matplotlib.pyplot as plt

folder_path = "Program/Sim_Data"

csv_files = [
    "0_4.csv",
    "0_2.csv",
    "0_0.csv",
    "4_2.csv",
    "4_4.csv",
]

output_image_name = "rocket_flight_trajectories_vertical.png"

plot_colors = ['#3FB6A4', '#25A18A', '#019A7B', '#017864', '#015A4A']

fig, axs = plt.subplots(nrows=1, ncols=5, figsize=(34, 9), sharey=True, sharex=True)

for i, file_path in enumerate(csv_files):
    df = pd.read_csv(os.path.join(folder_path, file_path))

    x = df['Position East of launch (m)']
    y = df['Altitude (m)']
    t = df['# Time (s)']  # 時間欄位
    
    axs[i].plot(x, y, color=plot_colors[i % len(plot_colors)], linewidth=2.5)
    
    wind_speed = (i - 2) * 2  # 對應的風速
    axs[i].set_title(f"Wind: {wind_speed:+} m/s", fontsize=18)
    axs[i].grid(True)

    # 找最高點
    idx_max = y.idxmax()
    x_max = x[idx_max]
    y_max = y[idx_max]
    t_max = t[idx_max]
    axs[i].scatter(x_max, y_max, color='red', s=60, label='Max Altitude')
    axs[i].annotate(f"{y_max:.1f} m\n{t_max:.1f} s",
                    (x_max, y_max),
                    textcoords="offset points",
                    xytext=(0, 10),
                    ha='left',
                    fontsize=12,
                    color='red')
    
    # 找落地點（最後一筆資料）
    x_land = x.iloc[-1]
    y_land = y.iloc[-1]
    t_land = t.iloc[-1]
    axs[i].scatter(x_land, y_land, color='blue', s=60, label='Landing Point')
    axs[i].annotate(f"{x_land:.1f} m\n{t_land:.1f} s",
                    (x_land, y_land),
                    textcoords="offset points",
                    xytext=(20, 5),
                    ha='left',
                    fontsize=12,
                    color='blue')
    
    axs[i].set_xlim(-50, 600)
    axs[i].set_ylim(-50, 1300)

    if i == 0:
        axs[i].set_ylabel("Altitude (m)", fontsize=16)

axs[-3].set_xlabel("Position East of Launch (m)", fontsize=16)

fig.tight_layout()
plt.savefig(output_image_name, bbox_inches='tight')
print(f"Image successfully saved as '{output_image_name}'")
plt.show()
