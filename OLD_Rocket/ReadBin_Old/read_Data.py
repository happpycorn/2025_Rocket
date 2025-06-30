import struct
import csv

# 定義 C++ TotalData 的對應 struct 格式
STRUCT_FORMAT = "f f f f 3f 3f 3f f f f 3? ? ? 2? ? ? ? d d f f I f f f B B f f B B B f f"
STRUCT_SIZE = struct.calcsize(STRUCT_FORMAT)

# CSV 欄位名稱
CSV_HEADERS = [
    "temperature", "pressure", "altitude", "humidity",
    "accel_x", "accel_y", "accel_z",
    "gyro_x", "gyro_y", "gyro_z",
    "mag_x", "mag_y", "mag_z",
    "aSqrt", "mDirection", "slope",
    "servo1", "servo2", "servo3",
    "chute1Failed", "chute2Failed",
    "barometer1", "barometer2", "accel", "hygro",
    "isHaveSensor",
    "latitude", "longitude", "gps_altitude", "geoidSeparation",
    "utcTime", "groundSpeed", "heading", "verticalSpeed",
    "numSatellites", "numVisibleSat",
    "hdop", "pdop", "signalQuality",
    "fixType", "gnssSystem", "accEst", "accVel"
]

def read_total_data(filename):
    data_list = []

    with open(filename, "rb") as f:
        while True:
            data = f.read(STRUCT_SIZE)
            if not data:
                break  # 讀取完畢

            if len(data) != STRUCT_SIZE:
                print(f"❌ 錯誤！讀取到 {len(data)} bytes, 但預期 {STRUCT_SIZE}")
                continue

            # 解析數據
            unpacked = struct.unpack(STRUCT_FORMAT, data)

            # 轉成字典
            sensor_data = {
                "temperature": unpacked[0],
                "pressure": unpacked[1],
                "altitude": unpacked[2],
                "humidity": unpacked[3],
                "accel_x": unpacked[4], "accel_y": unpacked[5], "accel_z": unpacked[6],
                "gyro_x": unpacked[7], "gyro_y": unpacked[8], "gyro_z": unpacked[9],
                "mag_x": unpacked[10], "mag_y": unpacked[11], "mag_z": unpacked[12],
                "aSqrt": unpacked[13],
                "mDirection": unpacked[14],
                "slope": unpacked[15],
                "servo1": unpacked[16], "servo2": unpacked[17], "servo3": unpacked[18],
                "chute1Failed": unpacked[19],
                "chute2Failed": unpacked[20],
                "barometer1": unpacked[21], "barometer2": unpacked[22],
                "accel": unpacked[23],
                "hygro": unpacked[24],
                "isHaveSensor": unpacked[25],
                "latitude": unpacked[26], "longitude": unpacked[27],
                "gps_altitude": unpacked[28], "geoidSeparation": unpacked[29],
                "utcTime": unpacked[30],
                "groundSpeed": unpacked[31], "heading": unpacked[32], "verticalSpeed": unpacked[33],
                "numSatellites": unpacked[34], "numVisibleSat": unpacked[35],
                "hdop": unpacked[36], "pdop": unpacked[37],
                "signalQuality": unpacked[38],
                "fixType": unpacked[39], "gnssSystem": unpacked[40],
                "accEst": unpacked[41], "accVel": unpacked[42]
            }

            # 加入數據列表
            data_list.append(sensor_data)

    return data_list

def save_to_csv(data_list, csv_filename):
    with open(csv_filename, mode="w", newline="") as f:
        writer = csv.DictWriter(f, fieldnames=CSV_HEADERS)
        writer.writeheader()  # 寫入 CSV 標題
        writer.writerows(data_list)  # 寫入數據

# 讀取二進制並轉存 CSV
data = read_total_data("Python/data.bin")
save_to_csv(data, "Data.csv")
print("✅ 轉換完成！數據已存入 Data.csv")
