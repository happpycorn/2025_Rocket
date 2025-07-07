#pragma once

#include "Constant.h"
#include <Wire.h>
#include "MPU9250.h"

class Accelerometer : public HFreqSensor {
public:
    Accelerometer(int addr) : HFreqSensor(addr) {}
    bool begin() override;
    bool getData(float data[]) override;
    
private:
    MPU9250 mpu;
};