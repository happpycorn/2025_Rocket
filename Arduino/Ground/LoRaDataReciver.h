#pragma once

#include "Constant.h"
#include <HardwareSerial.h>

class LoRaDataReciver {
public:
    struct ReciveData {
        int pack_count;
        float f[RECIVE_FLOAT_DATA_LEN];
        bool b[RECIVE_BOOL_DATA_LEN];
        double d[RECIVE_DOUBLE_DATA_LEN];
        bool is_data;
    };
    
    struct Result {
        char message[LORA_BUFFER_LEN];
        ReciveData data;
    };

    LoRaDataReciver();
    bool begin();
    Result reciveData();

private:
    HardwareSerial serial;
    int state = 0;
    int index = 0;
    uint8_t buffer[LORA_BUFFER_LEN];
    uint8_t type = 0;
    
    ReciveData decode(uint8_t code[], uint8_t check_code);
};
