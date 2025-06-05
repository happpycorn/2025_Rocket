import pandas as pd
import matplotlib.pyplot as plt

csv_files = [
    "Data/RocketSim-WS4.csv",
    "Data/RocketSim-WS2.csv",
    "Data/RocketSim-WS0.csv",
    "Data/RocketSim-WS-2.csv",
    "Data/RocketSim-WS-4.csv",
]

output_image_name = "rocket_flight_trajectories_vertical.png"

plot_colors = ['#3FB6A4', '#25A18A', '#019A7B', '#017864', '#015A4A']

fig, axs = plt.subplots(nrows=5, ncols=1, figsize=(10, 18), sharex=True)

for i, file_path in enumerate(csv_files):
    df = pd.read_csv(file_path)
    axs[i].plot(
        df['Position East of launch (m)'], df['Altitude (m)'],
        color=plot_colors[i % len(plot_colors)],
        linewidth=2.5
    )
    wind_speed = (i - 2) * 2  # 將 index 轉換成風速
    axs[i].set_title(f"Wind Speed: {wind_speed} m/s")
    axs[i].set_ylabel("Altitude (m)")
    axs[i].grid(True)

axs[-1].set_xlabel("Position East of Launch (m)")
fig.tight_layout()  # 不需要留空間給主標題了

plt.savefig(output_image_name)
print(f"Image successfully saved as '{output_image_name}'")

plt.show()
