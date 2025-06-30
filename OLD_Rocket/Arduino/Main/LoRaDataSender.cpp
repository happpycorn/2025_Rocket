#include "LoRaDataSender.h"

LoRaDataSender::LoRaDataSender() : serial(HardwareSerial(LORA_UART_CHANNEL)) {}

bool LoRaDataSender::begin() {
    serial.begin(LORA_BAUD, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
    return true;
}

void LoRaDataSender::sendData(float f_data[], bool b_data[], double d_data[]) {
    
    // Empty Package
    const int bufferSize = sizeof(int) + 3 * sizeof(float) + 2 + 2 * sizeof(double);
    uint8_t buffer[bufferSize];
    int index = 0;
    
    // Package count
    pack_count++;
    memcpy(&buffer[index], &pack_count, sizeof(int));
    index += sizeof(int);

    // Slope 3
    for (int i = SLOPE_DATA_ADDR; i < SLOPE_DATA_ADDR + 3; i++) {
        memcpy(&buffer[index], &f_data[i], sizeof(float));
        index += sizeof(float);
    }

    // Bool Data 11
    uint8_t boolByte1 = 0, boolByte2 = 0;
    for (int i = 0; i < 8; i++) {
        if (b_data[i]) boolByte1 |= (1 << i);
        Serial.print(b_data[i]);
    }
    for (int i = 8; i < LF_BOOL_DATA_LEN; i++) {
        if (b_data[i]) boolByte2 |= (1 << (i - 8));
        Serial.print(b_data[i]);
    }
    Serial.println();
    buffer[index++] = boolByte1;
    buffer[index++] = boolByte2;

    // GPS 2
    for (int i = 0; i < LF_DOUBLE_DATA_LEN; i++) {
        memcpy(&buffer[index], &d_data[i], sizeof(double));
        index += sizeof(double);
    }

    // Check sum
    uint8_t checksum = 0;
    for (int i = 0; i < bufferSize; i++) {
        checksum ^= buffer[i];
    }

    serial.write(HEADER1);
    serial.write(HEADER2);
    serial.write(0x01);

    serial.write(buffer, index);
    serial.write(checksum);
}

void LoRaDataSender::println(const String& content) {
    uint8_t len = content.length();  // 限 255 字元

    serial.write(HEADER1);
    serial.write(HEADER2);
    serial.write(0x02);
    serial.write(len);  // 字串長度
    serial.write((const uint8_t*)content.c_str(), len);  // 傳文字內容
}