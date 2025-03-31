#include "LoRaDataSender.h"

LoRaDataSender loRaDataSender;

void setup() {
    Serial.begin(115200);
    while (!Serial);
    if (!loRaDataSender.begin()) {
        Serial.println("LoRa initialization failed");
        return;
    }
}

void loop() {
    TotalData data;
    // 填充 TotalData 數據...
    loRaDataSender.sendTotalData(data);  // 發送數據
    delay(1000);
}