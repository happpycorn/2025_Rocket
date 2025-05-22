#include "LoRaDataSender.h"

LoRaDataSender::LoRaDataSender() : serial(HardwareSerial(LORA_UART_CHANNEL)) {}

bool LoRaDataSender::begin() {
    serial.begin(LORA_BAUD, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
    return true;
}

void LoRaDataSender::sendData(float f_data[], bool b_data[], double d_data[]) {
    
    // Empty Package
    const int bufferSize = sizeof(pack_count) + 3 * sizeof(float) + 2 + 2 * sizeof(double) + 1;
    uint8_t buffer[bufferSize];
    int index = 0;
    
    // Package count
    pack_count++;
    memcpy(&buffer[index], &pack_count, sizeof(pack_count));
    index += sizeof(pack_count);

    // Slope 3
    for (int i = SLOPE_DATA_ADDR; i < SLOPE_DATA_ADDR + 3; i++) {
        memcpy(&buffer[index], &f_data[i], sizeof(float));
        index += sizeof(float);
    }

    // Bool Data 11
    uint8_t boolByte1 = 0, boolByte2 = 0;
    for (int i = 0; i < 8; i++) {
        if (b_data[i]) boolByte1 |= (1 << i);
    }
    for (int i = 8; i < LF_BOOL_DATA_LEN; i++) {
        if (b_data[i]) boolByte2 |= (1 << (i - 8));
    }
    buffer[index++] = boolByte1;
    buffer[index++] = boolByte2;

    // GPS 2
    for (int i = 0; i < LF_DOUBLE_DATA_LEN; i++) {
        memcpy(&buffer[index], &d_data[i], sizeof(double));
        index += sizeof(double);
    }

    // Check sum
    uint8_t checksum = 0;
    for (int i = 0; i < index; i++) {
        checksum ^= buffer[i];
    }
    buffer[index++] = checksum;

    serial.write(0xAA);
    serial.write(0x55);
    serial.write(0x01);

    serial.write(buffer, index);
}

void LoRaDataSender::println(String content) {
    serial.write(0xAA);
    serial.write(0x55);
    serial.write(0x02);
    serial.println(content);
}