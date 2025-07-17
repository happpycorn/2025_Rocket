#include "Hygrometer.h"

Hygrometer hgyro;

void setup() {
    Serial.begin(115200);  // 初始化串口通信

    Wire.begin();

    if (!hgyro.begin()) {
        Serial.println("SHTC3 初始化失敗！");
        while (1);
    }

    Serial.println("SHTC3 初始化成功！");
}

void loop() {
    float temperature, humidity;

    // 獲取數據
    if (hgyro.getData(temperature, humidity)) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.print(" °C  ");

        Serial.print("Humidity: ");
        Serial.print(humidity);
        Serial.println(" %");

        Serial.println();  // 輸出空行
    } else {
        Serial.println("獲取數據失敗！");
    }

    delay(100);
}