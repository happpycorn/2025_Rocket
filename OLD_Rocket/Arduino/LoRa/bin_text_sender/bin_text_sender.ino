#include <HardwareSerial.h>

HardwareSerial LoRa(1);  // UART1

const uint8_t HEADER1 = 0xAA;
const uint8_t HEADER2 = 0x55;
const uint8_t TYPE_STRING = 0x02;

void sendString(const String& content) {
    uint8_t len = content.length();  // 限 255 字元

    LoRa.write(HEADER1);
    LoRa.write(HEADER2);
    LoRa.write(TYPE_STRING);
    LoRa.write(len);  // 字串長度
    LoRa.write((const uint8_t*)content.c_str(), len);  // 傳文字內容
}

void setup() {
    Serial.begin(115200);
    LoRa.begin(9600, SERIAL_8N1, 13, 14); // RX, TX
}

void loop() {
    sendString("Hello");
    Serial.println("Sent: Hello");
    delay(1000);
}
