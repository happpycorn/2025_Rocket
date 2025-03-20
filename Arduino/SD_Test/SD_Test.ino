#include "FS.h"
#include "SD.h"
#include "SPI.h"

#define SD_CS_PIN 5  // SD 卡模組的 CS 腳位

void setup() {
    Serial.begin(115200);

    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("⚠ SD 卡初始化失敗");
        return;
    }
    Serial.println("✅ SD 卡初始化成功");

    // 嘗試寫入 CSV 檔案
    File file = SD.open("/data.csv", FILE_WRITE);
    if (file) {
        // 寫入 CSV 資料，使用逗號分隔欄位
        file.println("Name,Age,Location");
        file.println("Alice,25,New York");
        file.println("Bob,30,Los Angeles");
        file.println("Charlie,22,Boston");

        file.close();
        Serial.println("✅ 成功寫入 data.csv");
    } else {
        Serial.println("❌ 無法寫入 data.csv");
    }
}

void loop() {
}
