import pandas as pd
from scipy.interpolate import interp1d
import numpy as np

def process_and_resample_data(csv_file):
    df = pd.read_csv(csv_file)
    # 將時間轉換為毫秒
    df['Time(ms)'] = df['Time'] * 1000
    df = df.drop(columns=['Time'])  # 移除原始的時間欄位

    # 找出原始時間的最小值和最大值
    start_time = df['Time(ms)'].min()
    end_time = df['Time(ms)'].max()

    # 建立新的時間序列，間隔為 10 毫秒
    new_time = np.arange(start_time, end_time + 10, 10)

    # 使用線性插值擬合 'Alt' 數值
    interpolation_function = interp1d(df['Time(ms)'], df['Alt'], kind='linear', fill_value="extrapolate")
    new_alt = interpolation_function(new_time)

    # 建立新的 DataFrame
    resampled_df = pd.DataFrame({'Time(ms)': new_time, 'Alt': new_alt})

    return resampled_df

# 指定你的 CSV 檔案路徑
csv_file_path = r'simData/Apogee-200-13s-simdata.csv'  # 將 'your_data.csv' 替換成你的檔案名稱

# 處理資料並取得重採樣後的 DataFrame
resampled_data = process_and_resample_data(csv_file_path)

# 如果處理成功，印出或儲存結果
if resampled_data is not None:
    print(resampled_data.head())  # 顯示前幾行
    # 可以將結果儲存到新的 CSV 檔案
    resampled_data.to_csv('resampled_data.csv', index=False)