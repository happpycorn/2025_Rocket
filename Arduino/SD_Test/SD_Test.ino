#include "SDDataManager.h"

SDDataManager sdManager;

void setup() {
    Serial.begin(115200);

    if (!sdManager.begin()) {
        Serial.println("初始化 SD 卡失敗!");
        while (1);
    }
    Serial.println("SD 卡初始化成功!");

    TotalData totaldata;
    sdManager.saveData(totaldata);
}

void loop() {
  // 這裡不需要任何操作，因為不需要讀取數據
}
