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

print("Apogee points (maximum altitude during flight):\n")

for i, file_path in enumerate(csv_files):
    df = pd.read_csv(os.path.join(folder_path, file_path))

    # 找出最高點（最大 Altitude）
    apogee_row = df.loc[df['Altitude (m)'].idxmax()]

    apogee_altitude = apogee_row['Altitude (m)']
    position_east = apogee_row['Position East of launch (m)']
    wind_speed = (i - 2) * -2

    # print(f"Wind Speed {wind_speed:>+3} m/s → Apogee: {apogee_altitude:.2f} m at {position_east:.2f} m East")

    print(apogee_altitude)
