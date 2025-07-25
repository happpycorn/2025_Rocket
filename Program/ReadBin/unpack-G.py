import csv
import struct
import os

data_path = 'Program/ReadBin/reciveData.bin'

# 參數定義
SLOPE_INDEX_MAX = 100
BOOL_DATA_LEN = 12
DOUBLE_DATA_LEN = 4
GPS_FLOAT_DATA_LEN = 10

# 建立 struct 格式
record_format = (
    'Q'                     # time: unsigned long long (8 bytes)
    'ii'                    # slope_index, warning_index: int (4+4)
    '??'                    # slope_overflow, warning_overflow: bool (1+1)
    f'{SLOPE_INDEX_MAX * 4}f'  # slope_data: float[10][4]
    '3f'                    # attit_data: float[3]
    f'{BOOL_DATA_LEN}?'     # rocket_state: bool[11]
    f'{DOUBLE_DATA_LEN}d'   # gps_data_d: double[2]
    f'{GPS_FLOAT_DATA_LEN}f'  # local_gps_data_f: float[10]
    'f'                     # max_alt: float
    'Q'                     # last_recive_time: unsigned long long
    'I'                     # recive_pack_count: unsigned int
)

record_size = struct.calcsize(record_format)

# 標籤
labels = [
    'time', 'slope_index', 'warning_index', 'slope_overflow', 'warning_overflow'
]
labels += [f'slope_data_{i}_{j}' for i in range(SLOPE_INDEX_MAX) for j in range(4)]
labels += ['attit_roll', 'attit_pitch', 'attit_yaw']
labels += [f'rocket_state_{i}' for i in range(BOOL_DATA_LEN)]
labels += ['gps_latitude', 'gps_longitude']
labels += [f'local_gps_data_{i}' for i in range(GPS_FLOAT_DATA_LEN)]
labels += ['max_alt', 'last_receive_time', 'receive_pack_count']

# 讀取函式
def read_data_bin(filename):
    records = []
    with open(filename, 'rb') as f:
        while True:
            chunk = f.read(record_size)
            if len(chunk) < record_size:
                break
            data = struct.unpack(record_format, chunk)
            records.append(data)
    return records

def read_last_n_records(filepath, n):
    records = []
    filesize = os.path.getsize(filepath)
    total_records = filesize // record_size
    n = min(n, total_records)

    with open(filepath, 'rb') as f:
        f.seek(-n * record_size, os.SEEK_END)  # 從尾部往前跳 n 筆
        for _ in range(n):
            chunk = f.read(record_size)
            if len(chunk) == record_size:
                data = struct.unpack(record_format, chunk)
                records.append(data)
    return records

# 寫入 CSV
if __name__ == '__main__':
    last_records = read_last_n_records(data_path, 100)
    with open('last_100_output.csv', 'w', newline='', encoding='utf-8-sig') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(labels)
        for record in last_records:
            writer.writerow(record)

    print(f"✅ 成功輸出最後 {len(last_records)} 筆資料到 last_100_output.csv")
