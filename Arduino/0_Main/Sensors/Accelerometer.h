#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <MPU9250_asukiaaa.h>

#define SDA_PIN 21
#define SCL_PIN 22

class Accelerometer {
public:
    // 初始化 MPU9250 並檢查連接
    bool begin(TwoWire* wire);
    
    // 讀取加速度、陀螺儀及磁場數據
    bool getData(float *accelOut, float *gyroOut, float *magOut, float &aSqrt, float &mDirection);

private:

    MPU9250_asukiaaa mpu;
};

#endif  // ACCELEROMETER_H
