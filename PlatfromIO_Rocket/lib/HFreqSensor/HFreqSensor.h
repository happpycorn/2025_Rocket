#pragma once

#include "Constant.h"

class HFreqSensor {
public:
    HFreqSensor(int addr) : data_addr(addr) {}
    virtual bool begin() = 0;
    virtual bool getData(float data[]) = 0;

protected:
    int data_addr;
};
