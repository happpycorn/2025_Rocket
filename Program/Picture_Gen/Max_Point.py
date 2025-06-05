import pandas as pd

csv_files = [
    "Data/RocketSim-WS-4.csv",
    "Data/RocketSim-WS-2.csv",
    "Data/RocketSim-WS0.csv",
    "Data/RocketSim-WS2.csv",
    "Data/RocketSim-WS4.csv",
]

print("Apogee points (maximum altitude during flight):\n")

for i, file_path in enumerate(csv_files):
    df = pd.read_csv(file_path)

    # 找出最高點（最大 Altitude）
    apogee_row = df.loc[df['Altitude (m)'].idxmax()]

    apogee_altitude = apogee_row['Altitude (m)']
    position_east = apogee_row['Position East of launch (m)']
    wind_speed = (i - 2) * -2

    print(f"Wind Speed {wind_speed:>+3} m/s → Apogee: {apogee_altitude:.2f} m at {position_east:.2f} m East")
