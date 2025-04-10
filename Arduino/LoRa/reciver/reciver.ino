#include <HardwareSerial.h>

HardwareSerial LoRa(1);  // 使用 UART1

void setup() {
  Serial.begin(115200);         // 給電腦看的 Serial
  LoRa.begin(9600, SERIAL_8N1, 14, 13);  // RX=13, TX=14
}

void loop() {
  if (LoRa.available()) {
    String received = LoRa.readStringUntil('\n');
    Serial.print("Received: ");
    Serial.println(received);
  }
}
