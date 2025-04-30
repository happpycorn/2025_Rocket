import struct

# 設定常數
LF_FLOAT_DATA_LEN = 33
LF_BOOL_DATA_LEN = 11
LF_DOUBLE_DATA_LEN = 2

# 每筆資料的大小（位元組）
ENTRY_SIZE = (
    4 * LF_FLOAT_DATA_LEN +
    1 * LF_BOOL_DATA_LEN +
    8 * LF_DOUBLE_DATA_LEN
)

# 格式字串：Little-endian、float、bool、double
STRUCT_FORMAT = f"<{LF_FLOAT_DATA_LEN}f{LF_BOOL_DATA_LEN}?{LF_DOUBLE_DATA_LEN}d"

# 上面那三個 LABEL 定義可以放這裡
LF_FLOAT_LABELS = [
    "BMP1_Temp", "BMP1_Pressure", "BMP1_Altitude",
    "BMP2_Temp", "BMP2_Pressure", "BMP2_Altitude",
    "Slope_X", "Slope_Y", "Slope_Z",
    "Acc_X1", "Acc_Y1", "Acc_Z1",
    "Acc_X2", "Acc_Y2", "Acc_Z2",
    "Acc_X3", "Acc_Y3", "Acc_Z3",
    "Acc_X4", "Acc_Y4", "Acc_Z4",
    "Gyro_X", "Gyro_Y",
    "GPS_0", "GPS_1", "GPS_2", "GPS_3", "GPS_4", "GPS_5",
    "GPS_6", "GPS_7", "GPS_8", "GPS_9", "GPS_10"
]

LF_BOOL_LABELS = [
    "Servo_1", "Servo_2", "Servo_3",
    "Fail_1", "Fail_2",
    "Sensor_1", "Sensor_2", "Sensor_3", "Sensor_4",
    "Is_HF_Data",
    "Is_GPS_Data"
]

LF_DOUBLE_LABELS = [
    "GPS_Latitude", "GPS_Longitude"
]


def read_lfreq_data_with_labels(filename):
    entries = []
    with open(filename, "rb") as file:
        index = 0
        while True:
            chunk = file.read(159)
            if not chunk:
                break
            if len(chunk) < 159:
                print(f"[警告] 第 {index} 筆資料不足 159 bytes，跳過")
                break

            unpacked = struct.unpack(STRUCT_FORMAT, chunk)

            floats_raw = unpacked[:33]
            bools_raw = unpacked[33:44]
            doubles_raw = unpacked[44:]

            # 建立帶標籤的 dict
            float_dict = dict(zip(LF_FLOAT_LABELS, floats_raw))
            bool_dict = dict(zip(LF_BOOL_LABELS, bools_raw))
            double_dict = dict(zip(LF_DOUBLE_LABELS, doubles_raw))

            entry = {
                "index": index,
                "float": float_dict,
                "bool": bool_dict,
                "double": double_dict
            }
            entries.append(entry)
            index += 1
    return entries

# 示範使用
if __name__ == "__main__":
    data_entries = read_lfreq_data_with_labels(r"Program\ReadBin\data.bin")
    for entry in data_entries:
        print(f"第 {entry['index']} 筆：")
        print("  [Float]")
        for k, v in entry['float'].items():
            print(f"    {k}: {v:.2f}")
        print("  [Bool]")
        for k, v in entry['bool'].items():
            print(f"    {k}: {v}")
        print("  [Double]")
        for k, v in entry['double'].items():
            print(f"    {k}: {v:.8f}")
        print("-" * 50)
