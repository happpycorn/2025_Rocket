import os
import pandas as pd

folder_path = "Program/Sim_Data"

csv_files = [
    "0_4.csv",
    "0_2.csv",
    "0_0.csv",
    "4_2.csv",
    "4_4.csv",
]

print("Landing points Data:")

for i, file_path in enumerate(csv_files):
    df = pd.read_csv(os.path.join(folder_path, file_path))

    # 找出高度最接近 0 的那一列（著陸點）
    landing_row = df.iloc[(df['Altitude (m)']).abs().idxmin()]

    position_east = landing_row['Position East of launch (m)']
    altitude = landing_row['Altitude (m)']
    wind_speed = (i - 2) * -2

    # print(f"Wind Speed {wind_speed:>+3} m/s → Landing Point Data: {position_east} (Altitude: {altitude:.2f} m)")

    print(position_east)
