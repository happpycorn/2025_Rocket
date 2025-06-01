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
#include <MPU9250_asukiaaa.h>

class Accelerometer : public HFreqSensor {
public:
    Accelerometer(int data_addr) : HFreqSensor(data_addr) {}
    bool begin() override;
    bool getData(float data[]) override;
    
private:
    MPU9250_asukiaaa mpu;
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