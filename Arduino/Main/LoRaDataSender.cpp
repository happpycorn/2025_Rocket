#include "LoRaDataSender.h"

LoRaDataSender::LoRaDataSender() : serial(HardwareSerial(LORA_UART_CHANNEL)) {}

bool LoRaDataSender::begin() {
    serial.begin(LORA_BAUD, SERIAL_8N1, LORA_RX_PIN, LORA_TX_PIN);
    return true;
}

void LoRaDataSender::sendData(float f_data[], bool b_data[], double d_data[]) {
    pack_count++;
    serial.print(pack_count); serial.print(",");

    // Slope
    for (int i = SLOPE_DATA_ADDR; i < SLOPE_DATA_ADDR+3; i++) {
        serial.print(f_data[i]); serial.print(",");
    }


    for (int i = 0; i < LF_BOOL_DATA_LEN; i++) {
        serial.print(b_data[i]); serial.print(",");
    }

    // GPS
    for (int i = 0; i < LF_DOUBLE_DATA_LEN; i++) {
        serial.print(d_data[i]); serial.print(",");
    }
    serial.print("\n");
}

void LoRaDataSender::println(String content) {
    serial.println(content);
}