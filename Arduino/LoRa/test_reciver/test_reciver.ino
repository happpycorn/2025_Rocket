#include <HardwareSerial.h>
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5  // SD卡的CS腳位（依照你的接法調整）

HardwareSerial LoRa(1);  // 使用 UART1

unsigned long lastReceiveTime = 0;  // 上一次收到封包的時間
File dataFile;  // SD卡上的檔案

void setup() {
    Serial.begin(115200);         
    LoRa.begin(9600, SERIAL_8N1, 14, 13);  // RX=13, TX=14

    // 初始化 SD 卡
    if (!SD.begin(SD_CS_PIN)) {
        Serial.println("SD Card initialization failed!");
        while (1);
    }
    Serial.println("SD Card initialized.");

    // 建立 CSV 並寫入標題列
    if (!SD.exists("/data.csv")) {
        dataFile = SD.open("/data.csv", FILE_APPEND);
        if (dataFile) {
            dataFile.println("Timestamp(ms),Interval(ms),RawData,ParsedInt");
            dataFile.close();
        } else {
            Serial.println("Error creating data.csv");
        }
    }

    delay(500);
    Serial.println("LoRa Receiver Ready");
}

void loop() {
    if (LoRa.available()) {
        String received = LoRa.readStringUntil('\n');
        received.trim();  // 移除前後空白或換行

        unsigned long now = millis();
        unsigned long delta = 0;
        if (lastReceiveTime != 0) {
            delta = now - lastReceiveTime;
        }
        lastReceiveTime = now;

        // 將收到的字串轉成 int
        int parsedValue = received.toInt();

        // 顯示在 Serial Monitor
        Serial.print("Time between packets: ");
        Serial.print(delta);
        Serial.println(" ms");
        Serial.print("Received: ");
        Serial.println(received);

        // 寫入 SD 卡 CSV
        dataFile = SD.open("/data.csv", FILE_APPEND);
        if (dataFile) {
            dataFile.print(now); dataFile.print(",");
            dataFile.print(delta); dataFile.print(",");
            dataFile.print(received); dataFile.print(",");
            dataFile.println(parsedValue);
            dataFile.close();
        } else {
            Serial.println("Error opening data.csv");
        }
    }
}
