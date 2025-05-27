#include "Barometer.h"

#define BMP390_I2C_ADDRESS 0x76
#define STANDARD_PRESSURE 1009.63

BMPController bmpController(BMP390_I2C_ADDRESS, STANDARD_PRESSURE);

void setup() {
    Serial.begin(115200);  // 初始化串口通信

    // 初始化 BMP280 感測器
    if (!bmpController.begin()) {
        Serial.println("BMP390 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    Serial.println("BMP390 初始化成功！");
}

void loop() {
    float temperature, pressure, altitude;

    // 獲取數據
    if (bmpController.getData(temperature, pressure, altitude)) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" hPa");

        Serial.print("Altitude: ");
        Serial.print(altitude);
        Serial.println(" meters");

        Serial.println();  // 輸出空行
    } else {
        Serial.println("獲取數據失敗！");
    }

    delay(100);
}