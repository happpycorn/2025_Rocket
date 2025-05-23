#pragma once

#include "Constant.h"
#include <HardwareSerial.h>

class LoRaDataReciver {
private:
    HardwareSerial serial;
    int state = 0;
    int index = 0;
    uint8_t buffer[LORA_BUFFER_LEN];
    uint8_t type = 0;
    
public:
    LoRaDataReciver();
    bool begin();
    Result reciveData();
    ReciveData decode(uint8_t code[], uint8_t check_code);

    struct ReciveData {
        int pack_count;
        float f[RECIVE_FLOAT_DATA_LEN];
        bool b[RECIVE_BOOL_DATA_LEN];
        double d[RECIVE_DOUBLE_DATA_LEN];
    };
    
    struct Result {
        char message[LORA_BUFFER_LEN];
        ReciveData data;
    };
};
