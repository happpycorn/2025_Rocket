import pandas as pd

# 請把 'your_file.csv' 換成你的檔名
df = pd.read_csv("Program/Sim_Data/0_0.csv")

# 列名清理（有些軟體會在標題加奇怪字元）
df.columns = [col.strip() for col in df.columns]

# 指定欄位名
velocity_col = "Vertical velocity (m/s)"
cd_col = "Drag coefficient (​)"  # 注意這邊的欄位名稱可能有特殊空格或不可見字元！

# 處理：找出速度第一次變正（起飛點）
launch_index = df[df[velocity_col] > 0].index[0]

# 找出最大速度的位置（假設是往上飛，速度越來越大）
max_velocity_index = df[velocity_col].idxmax()

# 取從起飛到最高速這段的資料
ascent_df = df.loc[launch_index:max_velocity_index]

# 計算平均阻力係數
average_cd = ascent_df[cd_col].mean()

print(f"加速階段（起飛至最高速）平均 Drag Coefficient (Cd): {average_cd:.4f}")
