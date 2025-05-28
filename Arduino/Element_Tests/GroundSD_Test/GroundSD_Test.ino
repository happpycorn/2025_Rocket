#include "SDDataManager.h"

SDDataManager sdManager;

RecordData generateTestData();

void setup() {
    Serial.begin(115200);
    Serial.print("開始初始化 SD 卡，CS = ");
    Serial.println(SD_CS_PIN);
    if (!sdManager.begin()) {
        Serial.println("初始化 SD 卡失敗!");
    }


    if (!sdManager.begin()) {
        Serial.println("初始化 SD 卡失敗!");
        while (1);
    }
    Serial.println("SD 卡初始化成功!");

    RecordData totaldata = generateTestData();

    if (sdManager.saveData(totaldata)) {
        Serial.println("SD 卡寫入成功!");
    } else {
        Serial.println("SD 卡寫入失敗!");
    }
}

void loop() {
  // 這裡不需要任何操作，因為不需要讀取數據
}

// **靜態測試數據**
RecordData generateTestData() {
    RecordData data;

    data.time = 2000;
    data.last_recive_time = 1000;
    data.recive_pack_count = 10;

    for (int i = 0; i < FLOAT_DATA_LEN; i++) data.f[i] = 0;
    for (int i = 0; i < BOOL_DATA_LEN; i++) data.b[i] = 0;
    for (int i = 0; i < DOUBLE_DATA_LEN; i++) data.d[i] = 0;

    return data;
}
