import os
import pandas as pd
from collections import Counter
from windrose import WindroseAxes
import matplotlib.pyplot as plt
import numpy as np

# === Load CSV ===
FOLDER_PATH = "Program/Sim_Data"
df = pd.read_csv(os.path.join(FOLDER_PATH, "wind_data.csv"))
output_image_name = "wind_directions.png"

# === Flatten all wind direction values into a list ===
wind_values = []
for col in df.columns[1:]:  # Skip first column (row index)
    wind_values += df[col].dropna().astype(int).tolist()

dirs_16 = [
    'N', 'NNE', 'NE', 'ENE', 'E', 'ESE', 'SE', 'SSE',
    'S', 'SSW', 'SW', 'WSW', 'W', 'WNW', 'NW', 'NNW'
]

# === Function to convert degrees into 16 compass directions (optional) ===
def direction_label_16(degree):
    idx = int(((degree + 11.25) % 360) // 22.5)
    return dirs_16[idx]

# === Count occurrences ===
direction_counts = Counter([direction_label_16(d) for d in wind_values])
most_common_dir = direction_counts.most_common(1)[0]

print(f"The most frequent wind direction is: {most_common_dir[0]}, appearing {most_common_dir[1]} times")
print("Full direction counts:")
for direction, count in direction_counts.most_common():
    print(f"{direction}: {count}")

# === Plot Windrose ===
wind_speeds = [1] * len(wind_values)  # Assume wind speed = 1 for all directions
print(wind_speeds)
wind_directions = np.array(wind_values)

ax = WindroseAxes.from_ax()

# Customize the direction labels on the plot (angles and corresponding compass directions)
# ax.set_xticklabels(['N', 'NNE', 'NE', 'ENE', 'E', 'ESE', 'SE', 'SSE', 
#                     'S', 'SSW', 'SW', 'WSW', 'W', 'WNW', 'NW', 'NNW'])

# Plot the windrose with normalized frequencies
ax.bar(wind_directions, wind_speeds, normed=True, opening=0.8, edgecolor='white')

ax.set_title("Wind Rose Diagram (Wind Direction Distribution)")
# ax.set_legend(title="Frequency (%)")

plt.savefig(output_image_name, dpi=500)

plt.show()
