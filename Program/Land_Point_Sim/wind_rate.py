# 已出現的風向與次數
direction_counts = {
    "NNE": 20, "NE": 20, "SSE": 20, "SSW": 19, "SE": 15, "SW": 13,
    "ENE": 12, "N": 11, "S": 10, "ESE": 10, "E": 5, "NW": 3,
    "WNW": 2, "W": 1, "NNW": 1
}

# 每個風向對應角度（風從哪吹來）
direction_angles = {
    "N": 0, "NNE": 22.5, "NE": 45, "ENE": 67.5, "E": 90, "ESE": 112.5,
    "SE": 135, "SSE": 157.5, "S": 180, "SSW": 202.5, "SW": 225,
    "W": 270, "WNW": 292.5, "NW": 315, "NNW": 337.5
}

# 轉成機率 + 角度 list
total = sum(direction_counts.values())
wind_directions = []
wind_probs = []

for d, count in direction_counts.items():
    wind_directions.append(direction_angles[d])
    wind_probs.append(count / total)

print(wind_probs)