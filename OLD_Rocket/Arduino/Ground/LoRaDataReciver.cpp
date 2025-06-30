#include "LoRaDataReciver.h"

LoRaDataReciver::LoRaDataReciver() : serial(HardwareSerial(LORA_UART_CHANNEL)) {}

bool LoRaDataReciver::begin() {
    serial.begin(LORA_BAUD, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
    return true;
}

LoRaDataReciver::Result LoRaDataReciver::reciveData() {
    Result result;

    while (serial.available()) {
        uint8_t b = serial.read();

        switch (state) {
                
            case 0:  // 等待 0xAA
                if (b == HEADER1) state = 1;
                break;

            case 1:  // 等待 0x55
                if (b == HEADER2) state = 2;
                else state = 0;
                break;

            case 2:  // 讀取 type
                type = b;
                index = 0;
                state = 3;
                break;

            case 3:  // 根據 type 收資料
                if (type == 0x01) {  // binary 封包
                    buffer[index++] = b;
                    if (index >= BINARY_LENGTH) state = 5;  // 資料收滿
                } else if (type == 0x02) {  // 文字訊息（簡化做法）
                    len = b;
                    state = 4;
                } else {
                    state = 0;  // 未知類型
                }
                break;
            
            case 4:
                buffer[index++] = b;
                if (index == (int)len) state = 6;

            case 5:  // 收完二進位封包 → 下一 byte 是 checksum
                result.data = decode(buffer, b);
                state = 0;
                return result;
                
            case 6:  // 收完文字訊息
                buffer[index] = '\0';  // null 結尾
                strcpy(result.message, (char*)buffer);
                state = 0;
                return result;
        }
    }

    return result;
}

LoRaDataReciver::ReciveData LoRaDataReciver::decode(uint8_t code[], uint8_t check_code) {
    ReciveData data;

    uint8_t checksum = 0;
    for (int i = 0; i < index; i++) checksum ^= buffer[i];

    if (checksum != check_code) {
        data.is_data = false;
        return data;
    }

    // Package count
    memcpy(&data.pack_count, &buffer[index], sizeof(int));
    index += sizeof(int);

    // Float
    for (int i = 0; i < RECIVE_FLOAT_DATA_LEN; i++) {
        memcpy(&data.f[i], &buffer[index], sizeof(float));
        index += sizeof(float);
    }

    // Bool
    uint8_t boolByte1 = buffer[index++];
    uint8_t boolByte2 = buffer[index++];
    for (int i = 0; i < 8; i++) {
        data.b[i] = (boolByte1 & (1 << i)) != 0;
    }
    for (int i = 8; i < RECIVE_BOOL_DATA_LEN; i++) {
        data.b[i] = (boolByte2 & (1 << (i - 8))) != 0;
    }

    // Double
    for (int i = 0; i < 2; i++) {
        memcpy(&data.d[i], &buffer[index], sizeof(double));
        index += sizeof(double);
    }

    data.is_data = true;
    return data;
}