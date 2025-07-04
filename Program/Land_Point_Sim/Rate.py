import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import gaussian_kde
from tqdm import tqdm

output_image_name = "Landing_point_rate.png"

direction_counts = {
    "NNE": 20, "NE": 20, "SSE": 20, "SSW": 19, "SE": 15, "SW": 13,
    "ENE": 12, "N": 11, "S": 10, "ESE": 10, "E": 5, "NW": 3,
    "WNW": 2, "W": 1, "NNW": 1, "WSW":0
}

# 每個方向對應的角度範圍（degree），左閉右開
direction_angle_ranges = {
    "N": (348.75, 11.25),
    "NNE": (11.25, 33.75),
    "NE": (33.75, 56.25),
    "ENE": (56.25, 78.75),
    "E": (78.75, 101.25),
    "ESE": (101.25, 123.75),
    "SE": (123.75, 146.25),
    "SSE": (146.25, 168.75),
    "S": (168.75, 191.25),
    "SSW": (191.25, 213.75),
    "SW": (213.75, 236.25),
    "WSW": (236.25, 258.75),
    "W": (258.75, 281.25),
    "WNW": (281.25, 303.75),
    "NW": (303.75, 326.25),
    "NNW": (326.25, 348.75),
}

N = 10000

total = sum(direction_counts.values())
direction_probs = {k: v / total for k, v in direction_counts.items()}
base_prob = 0.001
new_probs_unnormalized = {k: p + base_prob for k, p in direction_probs.items()}
total_new = sum(new_probs_unnormalized.values())
new_direction_probs = {k: v / total_new for k, v in new_probs_unnormalized.items()}

speeds = np.random.uniform(0, 4, N)
directions = np.random.choice(list(new_direction_probs.keys()), size=N, p=list(new_direction_probs.values()))

xs, ys = [], []

for i in tqdm(range(N)):
    s = speeds[i]
    d = directions[i]
    low, high = direction_angle_ranges[d]

    # 角度處理：如果low > high，代表跨越0度，比如N方向
    if low > high:
        # 取一個角度，隨機從[low,360)和[0,high)兩段
        angle_deg = np.random.choice([
            np.random.uniform(low, 360),
            np.random.uniform(0, high)
        ])
    else:
        angle_deg = np.random.uniform(low, high)

    theta = np.radians(angle_deg)

    dx = (35 * s * np.sin(theta) + 360) 
    dy = (32.9 * s * np.cos(theta) - 1)

    xs.append(dx)
    ys.append(dy)

xy = np.vstack([xs, ys])
z = gaussian_kde(xy, bw_method=0.3)(xy)

plt.figure(figsize=(10, 6))
plt.scatter(xs, ys, c=z, s=2, cmap='turbo', alpha=0.8)
plt.title("Landing Point Probability Map (Angle Ranges)")
plt.xlabel("X (m)")
plt.ylabel("Y (m)")
plt.axis('equal')
plt.colorbar(label='Density')
plt.grid(True)
plt.tight_layout()
plt.savefig(output_image_name, dpi=500)
plt.show()
