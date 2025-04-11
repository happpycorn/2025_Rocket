#include <HardwareSerial.h>
#include "BluetoothSerial.h"

BluetoothSerial BTSerial;
HardwareSerial LoRa(2);  // UART1

#define LORA_RX 13
#define LORA_TX 14
#define AUX_PIN 4

unsigned long lastSend = 0;

void setup() {
    Serial.begin(115200);
    Serial.println("Booting...");
    pinMode(AUX_PIN, INPUT);

    // 初始化 LoRa UART
    LoRa.begin(9600, SERIAL_8N1, LORA_RX, LORA_TX);
    Serial.println("Booting...");

    // 啟用藍牙序列埠，手機可以連線看 log
    BTSerial.begin("LoRa_Debugger");  // 藍牙設備名稱
    Serial.println("Booting...");

    BTSerial.println("LoRa Debugger Ready");
}

void loop() {
    // 每秒檢查一次 AUX 狀態
    static unsigned long lastCheck = 0;
    if (millis() - lastCheck > 1000) {
        lastCheck = millis();
        int aux = digitalRead(AUX_PIN);
        BTSerial.print("AUX is ");
        BTSerial.println(aux == HIGH ? "HIGH (idle)" : "LOW (busy)");
    }

    // 每 3 秒傳一筆資料
    if (millis() - lastSend > 3000) {
        lastSend = millis();

        if (digitalRead(AUX_PIN) == HIGH) {
            LoRa.println("Hello from Bluetooth debug node!");
            BTSerial.println("Sent: Hello from Bluetooth debug node!");
        } else {
            BTSerial.println("AUX busy, skipping send");
        }
    }
}
