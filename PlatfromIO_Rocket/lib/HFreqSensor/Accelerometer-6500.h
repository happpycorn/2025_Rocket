#pragma once

#include "HFreqSensor.h"
#include <Wire.h>

#define MPU_ADDR 0x68  // MPU-6500 的預設 I2C 位址（AD0 接 GND）

// 寄存器定義
#define WHO_AM_I     0x75
#define PWR_MGMT_1   0x6B
#define ACCEL_XOUT_H 0x3B
#define GYRO_XOUT_H  0x43

class Accelerometer : public HFreqSensor {
public:
    Accelerometer(int data_addr) : HFreqSensor(data_addr) {}
    bool begin() override;
    bool getData(float data[]) override;
    
private:
    uint8_t readRegister(uint8_t addr, uint8_t reg);
    void writeRegister(uint8_t addr, uint8_t reg, uint8_t val);
};