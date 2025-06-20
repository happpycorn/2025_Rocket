#pragma once

#include "HFreqSensor.h"
#include <Adafruit_SHTC3.h>

class Hygrometer : public HFreqSensor{
public:
    Hygrometer(int data_addr) : HFreqSensor(data_addr) {}
    bool begin() override;
    bool getData(float data[]) override;

private:
    Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
};
