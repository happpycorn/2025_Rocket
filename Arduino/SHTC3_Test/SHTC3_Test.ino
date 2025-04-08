#include "Hygrometer.h"

Hygrometer hgyro;

void setup() {
    Serial.begin(115200);  // 初始化串口通信

    Wire.begin();

    // 初始化 BMP280 感測器
    if (!hgyro.begin()) {
        Serial.println("BMP390 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    Serial.println("BMP390 初始化成功！");
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