#include <HardwareSerial.h>

HardwareSerial LoRa(2);  // UART1

const uint8_t HEADER1 = 0xAA;
const uint8_t HEADER2 = 0x55;
const uint8_t TYPE_BINARY = 0x01;

// 根據你的 decode 設計
const int FLOAT_LEN = 3;           // RECIVE_FLOAT_DATA_LEN
const int BOOL_LEN = 11;           // RECIVE_BOOL_DATA_LEN
const int DOUBLE_LEN = 2;          // 2 doubles
const int PAYLOAD_LEN = sizeof(int) + FLOAT_LEN * sizeof(float) + 2 + DOUBLE_LEN * sizeof(double);  // +2 是 bool 壓成 2 bytes

void sendTestPacket(int packetID) {
    uint8_t buffer[PAYLOAD_LEN];
    int index = 0;

    // --- 1. 加入封包編號 ---
    memcpy(&buffer[index], &packetID, sizeof(int));
    index += sizeof(int);

    // --- 2. 加入 float 數值 ---
    for (int i = 0; i < FLOAT_LEN; i++) {
        float f = 1.11 * (i + 1);  // 任意測試值
        memcpy(&buffer[index], &f, sizeof(float));
        index += sizeof(float);
    }

    // --- 3. 加入 bool（壓成 2 bytes） ---
    uint8_t boolByte1 = 0b10101010;  // 8 個 bool
    uint8_t boolByte2 = 0b00000111;  // 剩下 4 個 bool
    buffer[index++] = boolByte1;
    buffer[index++] = boolByte2;

    // --- 4. 加入 double 數值 ---
    for (int i = 0; i < DOUBLE_LEN; i++) {
        double d = 123.456 + i;
        memcpy(&buffer[index], &d, sizeof(double));
        index += sizeof(double);
    }

    // --- 5. 計算 checksum（payload XOR）---
    uint8_t checksum = 0;
    for (int i = 0; i < PAYLOAD_LEN; i++) {
        checksum ^= buffer[i];
    }

    // --- 6. 寄出封包 ---
    LoRa.write(HEADER1);
    LoRa.write(HEADER2);
    LoRa.write(TYPE_BINARY);
    LoRa.write(buffer, PAYLOAD_LEN);
    LoRa.write(checksum);

    Serial.println("Sent test packet #" + String(packetID));
}

int packetID = 0;

void setup() {
    Serial.begin(115200);
    LoRa.begin(9600, SERIAL_8N1, 13, 14); // RX, TX
}

void loop() {
    sendTestPacket(packetID++);
    delay(1000);
}
