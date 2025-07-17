#pragma once

#include "Constant.h"
#include <Adafruit_BMP3XX.h>

class BMPController : public HFreqSensor {
public:
    BMPController(uint8_t iicaddr, float std_pressure, int data_addr)
        : HFreqSensor(data_addr), iicAddr(iicaddr), std_pressure(std_pressure) {}
    bool begin() override;
    bool getData(float data[]) override;

private:
    Adafruit_BMP3XX bmp;
    uint8_t iicAddr;
    float std_pressure;
};