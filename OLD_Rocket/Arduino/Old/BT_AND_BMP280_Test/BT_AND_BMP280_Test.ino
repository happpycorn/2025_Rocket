#include <Wire.h>
#include <Adafruit_BMP280.h>
#include "BluetoothSerial.h"

// I²C 設定
#define SDA_PIN 21
#define SCL_PIN 22
Adafruit_BMP280 bmp;

// 建立藍牙序列埠
BluetoothSerial SerialBT;

void setup() {
    Serial.begin(115200);  // USB 串口監視
    SerialBT.begin("ESP32_BMP280");  // 設定藍牙名稱

    // 初始化 I²C
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!bmp.begin(0x76)) {
        Serial.println("❌ BMP280 初始化失敗！");
        while (1);
    }

    // 設定 BMP280 讀取參數
    bmp.setSampling(Adafruit_BMP280::MODE_NORMAL,
                    Adafruit_BMP280::SAMPLING_X2,
                    Adafruit_BMP280::SAMPLING_X16,
                    Adafruit_BMP280::FILTER_X16,
                    Adafruit_BMP280::STANDBY_MS_500);

    Serial.println("✅ 藍牙已啟動，請用手機連線到 ESP32_BMP280");
}

void loop() {
    // 讀取感測數據
    float temperature = bmp.readTemperature();
    float pressure = bmp.readPressure() / 100.0; // hPa

    // 顯示數據到 USB 串口監視器
    Serial.print("🌡 溫度: ");
    Serial.print(temperature);
    Serial.print(" °C, ");
    Serial.print("⏬ 氣壓: ");
    Serial.print(pressure);
    Serial.println(" hPa");

    // 發送數據到藍牙
    SerialBT.print(millis());
    SerialBT.print(", ");
    SerialBT.print(temperature);
    SerialBT.print(", ");
    SerialBT.println(pressure);

    Serial.println("✅ 已透過藍牙傳輸數據！");

    delay(10); // 每秒發送一次數據
}
