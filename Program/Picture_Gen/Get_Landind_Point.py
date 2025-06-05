import pandas as pd

csv_files = [
    "Data/RocketSim-WS-4.csv",
    "Data/RocketSim-WS-2.csv",
    "Data/RocketSim-WS0.csv",
    "Data/RocketSim-WS2.csv",
    "Data/RocketSim-WS4.csv",
]

print("Landing points Data:\n")

for i, file_path in enumerate(csv_files):
    df = pd.read_csv(file_path)

    # 找出高度最接近 0 的那一列（著陸點）
    landing_row = df.iloc[(df['Altitude (m)']).abs().idxmin()]

    position_east = landing_row['Time (s)']
    altitude = landing_row['Altitude (m)']
    wind_speed = (i - 2) * -2

    print(f"Wind Speed {wind_speed:>+3} m/s → Landing Point Data: {position_east} (Altitude: {altitude:.2f} m)")
