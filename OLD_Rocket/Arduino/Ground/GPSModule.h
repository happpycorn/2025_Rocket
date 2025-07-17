#pragma once

#include <math.h>  // for NAN
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include "Constant.h"

class GPSModule{
private:
    TinyGPSPlus gps;
    HardwareSerial serial;
    int data_addr;

public:
    GPSModule(int addr);
    bool begin();
    bool getData(double d_data[], float f_data[]);
};
