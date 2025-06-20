#pragma once

#include "HFreqSensor.h"
#include <Wire.h>
#include <MPU9250.h>
#include <MadgwickAHRS.h>

class Accelerometer : public HFreqSensor {
public:
    Accelerometer(int data_addr) : HFreqSensor(data_addr) {}
    bool begin() override;
    bool getData(float data[]) override;
    
private:
    MPU9250 mpu;
    Madgwick filter;
};