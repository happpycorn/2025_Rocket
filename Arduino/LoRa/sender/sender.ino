#include <HardwareSerial.h>

HardwareSerial LoRa(1);  // 使用 UART1

// 發射端（ESP32）

unsigned long lastSendTime = 0;
int sendInterval = 1000;  // 每 1 秒傳一次
uint16_t packetID = 0;

void setup() {
    Serial.begin(115200);      // Debug 輸出
    LoRa.begin(9600, SERIAL_8N1, 14, 13);
}

void loop() {
    if (millis() - lastSendTime >= sendInterval) {
        lastSendTime = millis();

        // 準備資料
        char buffer[20];
        sprintf(buffer, "%u", packetID++);

        // 傳送資料
        LoRa.println(buffer);
        Serial.println("Sent: " + String(buffer));
    }
}
