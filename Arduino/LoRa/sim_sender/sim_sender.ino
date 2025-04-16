#include <HardwareSerial.h>

#define M0_PIN 22  // M0 接 GND 用於正常傳輸模式
#define M1_PIN 23  // M1 接 GND 用於正常傳輸模式

HardwareSerial LoRa(1);  // 使用 UART1

int send_count = 0;

void setup() {
    Serial.begin(115200);  
    // 設置與 LoRa 模組通訊的串口，波特率需與模組相符（這裡用 9600 為例）
    LoRa.begin(9600, SERIAL_8N1, 14, 13);  // RX=13, TX=14
    
    // 設置 M0、M1 引腳為輸出並拉低，讓模組進入正常傳輸模式
    pinMode(M0_PIN, OUTPUT);
    pinMode(M1_PIN, OUTPUT);
    digitalWrite(M0_PIN, LOW);
    digitalWrite(M1_PIN, LOW);
    
    delay(500);
    Serial.println("LoRa Sender Ready");
}

void loop() {
    send_count++;
    LoRa.println(send_count);
    Serial.println("Sent: PING");
    delay(1000);
}
