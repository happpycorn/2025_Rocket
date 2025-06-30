#include "SDDataManager.h"

SDDataManager sdManager;

TotalData generateTestData();

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

    TotalData totaldata = generateTestData();

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
TotalData generateTestData() {
    TotalData data;

    save_data.time = data.time;
    save_data.last_recive_time = data.last_recive_time;
    save_data.recive_pack_count = data.recive_pack_count;

    for (int i = 0; i < FLOAT_DATA_LEN; i++) save_data.f[i] = data.f[i];
    for (int i = 0; i < BOOL_DATA_LEN; i++) save_data.b[i] = data.b[i];
    for (int i = 0; i < DOUBLE_DATA_LEN; i++) save_data.d[i] = data.d[i];

    return data;
}
