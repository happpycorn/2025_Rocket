#pragma once

#include "Constant.h"
#include <HardwareSerial.h>

class LoRaDataSender {
private:
    HardwareSerial serial;
    const int bufferSize = sizeof(int) + 3 * sizeof(float) + 2 + 2 * sizeof(double);
    
public:
    int pack_count = 0;
    LoRaDataSender();
    bool begin();
    void sendData(float f_data[], bool b_data[], double d_data[]);
    void println(const String& content);
};
