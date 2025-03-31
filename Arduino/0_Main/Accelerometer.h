#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <MPU9250.h>

class Accelerometer {
public:
    // 初始化 MPU9250 並檢查連接
    bool begin();
    
    // 讀取加速度、陀螺儀及磁場數據
    bool getData(float accelOut[3], float gyroOut[3], float magOut[3]);

private:
    MPU9250 mpu;
};

#endif  // ACCELEROMETER_H
