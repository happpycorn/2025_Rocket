#include <HardwareSerial.h>

HardwareSerial LoRa(1);  // 使用 UART1

void setup() {
  Serial.begin(115200);         // 給電腦的 Serial
  LoRa.begin(9600, SERIAL_8N1, 14, 13);  // RX=13, TX=14
}

void loop() {
  LoRa.println("Hello LoRa!");
  Serial.println("Sent: Hello LoRa!");
  delay(1000);
}
