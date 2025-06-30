#pragma once

#include "Constant.h"
#include <HardwareSerial.h>

class LoRaDataSender {
private:
    HardwareSerial serial;
    
public:
    int pack_count = 0;
    LoRaDataSender();
    bool begin();
    void sendData(float f_data[], bool b_data[], double d_data[]);
    void println(const String& content);
};
