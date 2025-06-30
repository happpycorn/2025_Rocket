#pragma once

#include "Constant.h"
#include <HardwareSerial.h>

class LoRaDataReciver {
public:
    LoRaDataReciver();
    bool begin();
    Result reciveData();

private:
    HardwareSerial serial;
    int state = 0;
    int index = 0;
    uint8_t buffer[LORA_BUFFER_LEN];
    uint8_t type = 0;
    uint8_t len = 0;
    
    ReciveData decode(uint8_t code[], uint8_t check_code);
};
