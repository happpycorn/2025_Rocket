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
    
    axs[i].plot(
        df['Position East of launch (m)'], df['Altitude (m)'],
        color=plot_colors[i % len(plot_colors)],
        linewidth=2.5
    )
    
    wind_speed = (i - 2) * 2  # 轉換 index 為風速
    axs[i].set_title(f"Wind: {wind_speed:+} m/s", fontsize=18)
    axs[i].grid(True)
    
    # 只在最左邊加 y 標籤
    if i == 0:
        axs[i].set_ylabel("Altitude (m)", fontsize=16)
    
    # 可選：設 x/y 軸範圍統一（你可以觀察落點差距是否需要）
    # axs[i].set_xlim(-150, 150)
    # axs[i].set_ylim(0, 1400)

# 最右邊加 x 標籤
axs[-3].set_xlabel("Position East of Launch (m)", fontsize=16)

# 整體標題
# fig.suptitle("Rocket Flight Trajectories under Different Wind Speeds", fontsize=22, y=1.02)

fig.tight_layout()
plt.savefig(output_image_name, bbox_inches='tight')
print(f"Image successfully saved as '{output_image_name}'")
plt.show()
