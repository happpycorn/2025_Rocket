#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP280.h>

Adafruit_BMP280 bmp;  // 預設 I²C 地址 0x76

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22); // SDA = GPIO 21, SCL = GPIO 22
    
    if (!bmp.begin(0x77)) {  // 如果 0x76 無效，試試 0x77
        Serial.println("無法偵測 BMP280, 請檢查接線！");
        while (1);
    }
}

void loop() {
    Serial.print("氣壓: ");
    Serial.print(bmp.readPressure() / 100.0);  // hPa
    Serial.print(" hPa, 溫度: ");   
    Serial.print(bmp.readTemperature());
    Serial.println(" °C");

    delay(1000);
}
