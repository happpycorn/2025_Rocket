#ifndef ACCELEROMETER_H
#define ACCELEROMETER_H

#include <Wire.h>
#include <MPU6050.h>  // 假設你正在使用 MPU6050 函式庫

class Accelerometer {
public:

    bool begin();  // 用於初始化 MPU6050 和檢查連接
    bool getData(float accelOut[3], float gyroOut[3]);  // 更新加速度和陀螺儀數據

private:

    MPU6050 mpu;
    static constexpr int N = 10;  // 取最近 10 次讀數平均
    float accel_buf[N][3] = {0};  // ax, ay, az
    float gyro_buf[N][3] = {0};   // gx, gy, gz
    int index = 0;

    float getAverage(int axis, float buf[][3]);  // 獲取平滑平均值
};

#endif  // ACCELEROMETER_H
