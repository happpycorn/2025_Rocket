#include "0_Config.h"
#include "LoRaDataSender.h"

LoRaDataSender sender(Serial1, 9600, 12, 13); // 初始化時就決定通訊參數

void setup() {
    Serial.begin(115200);
    sender.begin(); // 更簡單

    TotalData data;

    sender.sendTotalData(data);
    Serial.println("finish");
}

void loop() {}
