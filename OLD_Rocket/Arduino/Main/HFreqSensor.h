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

#include <Adafruit_SHTC3.h>

class Hygrometer : public HFreqSensor{
public:
    Hygrometer(int data_addr) : HFreqSensor(data_addr) {}
    bool begin() override;
    bool getData(float data[]) override;

private:
    Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
};