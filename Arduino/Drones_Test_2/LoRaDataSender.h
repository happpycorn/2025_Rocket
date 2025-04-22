#pragma once

#include "Constant.h"
#include <HardwareSerial.h>

class LoRaDataSender {
private:
    HardwareSerial serial;
    int pack_count = 0;
    
public:
    LoRaDataSender();
    bool begin();
    void sendData(float f_data[], bool b_data[], double d_data[]);
    void println(String content);
};
