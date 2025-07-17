import csv
import struct

data_path = 'Program/ReadBin/data.bin'

LF_FLOAT_DATA_LEN = 34
LF_BOOL_DATA_LEN = 11
LF_DOUBLE_DATA_LEN = 2

record_format = f'{LF_FLOAT_DATA_LEN}f {LF_BOOL_DATA_LEN}? {LF_DOUBLE_DATA_LEN}d'
record_size = struct.calcsize(record_format)

labels = [
    "index", 
    "BMP1_Temp", "BMP1_Pressure", "BMP1_Altitude",
    "BMP2_Temp", "BMP2_Pressure", "BMP2_Altitude",
    "Slope_X", "Slope_Y", "Slope_Z",
    "Acc_X1", "Acc_Y1", "Acc_Z1",
    "Acc_X2", "Acc_Y2", "Acc_Z2",
    "Acc_X3", "Acc_Y3", "Acc_Z3",
    "Acc_X4", "Acc_Y4", "Acc_Z4",
    "Gyro_X", "Gyro_Y",
    "GPS_0", "GPS_1", "GPS_2", "GPS_3", "GPS_4", "GPS_5",
    "GPS_6", "GPS_7", "GPS_8", "GPS_9", "GPS_10",
    "Servo_1", "Servo_2", "Servo_3",
    "Fail_1", "Fail_2",
    "Sensor_1", "Sensor_2", "Sensor_3", "Sensor_4",
    "Is_HF_Data", "Is_GPS_Data",
    "GPS_Latitude", "GPS_Longitude"
]

def read_data_bin(filename):
    records = []

    with open(filename, 'rb') as f:
        while True:
            chunk = f.read(record_size)
            if len(chunk) < record_size:
                break
            data = struct.unpack(record_format, chunk)
            record = {
                'f': data[:LF_FLOAT_DATA_LEN],
                'b': data[LF_FLOAT_DATA_LEN:LF_FLOAT_DATA_LEN+LF_BOOL_DATA_LEN],
                'd': data[-LF_DOUBLE_DATA_LEN:]
            }
            records.append(record)
    return records

# 範例：讀取並印出所有資料
if __name__ == '__main__':
    data = read_data_bin(data_path)
    with open('output.csv', 'w', newline='', encoding='utf-8-sig') as csvfile:
        writer = csv.writer(csvfile)
        writer.writerow(labels)
        for idx, record in enumerate(data):
            row = [idx] + list(record['f']) + list(record['b']) + list(record['d'])
            writer.writerow(row)

    print(f"✅ 成功輸出 {len(data)} 筆資料到 output.csv")
