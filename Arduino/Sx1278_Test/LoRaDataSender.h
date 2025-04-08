#ifndef LORA_DATA_SENDER_H
#define LORA_DATA_SENDER_H

#include <Arduino.h>
#include "0_Config.h"

class LoRaDataSender {
public:
    LoRaDataSender(HardwareSerial& serial, uint32_t baud = 9600, int8_t rxPin = 12, int8_t txPin = 13)
        : loraSerial(serial), baudRate(baud), rx(rxPin), tx(txPin) {}

    void begin();
    void sendTotalData(const TotalData &data);

private:
    HardwareSerial& loraSerial;
    uint32_t baudRate;
    int8_t rx, tx;

    void serializeTotalData(const TotalData &data, byte *buffer, size_t &len);
    void sendBufferAsHex(byte* buffer, size_t len);
};

#endif
