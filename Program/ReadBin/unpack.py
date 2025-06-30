import struct

# 定義資料長度（要與 C++ 定義一致）
LF_FLOAT_DATA_LEN = 34
LF_BOOL_DATA_LEN = 11
LF_DOUBLE_DATA_LEN = 2

# 每筆資料的格式：5 個 float、3 個 bool（儲存成 1 byte）、2 個 double
record_format = f'{LF_FLOAT_DATA_LEN}f {LF_BOOL_DATA_LEN}? {LF_DOUBLE_DATA_LEN}d'
record_size = struct.calcsize(record_format)

print(f"每筆記錄大小: {record_size} bytes")

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
    data = read_data_bin('Program/ReadBin/data.bin')
    for i, record in enumerate(data):
        print(f"Record {i}:")
        print(f"  float:  {record['f']}")
        print(f"  bool:   {record['b']}")
        print(f"  double: {record['d']}")
