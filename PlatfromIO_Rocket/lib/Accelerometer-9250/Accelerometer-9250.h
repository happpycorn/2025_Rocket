#pragma once

#include "Constant.h"
#include <Wire.h>
#include "MPU9250.h"

class Accelerometer {
public:
    Accelerometer(int addr) : data_addr(addr) {}
    bool begin();
    bool getData(float data[]);
    
private:
    MPU9250 mpu;
    int data_addr;
};