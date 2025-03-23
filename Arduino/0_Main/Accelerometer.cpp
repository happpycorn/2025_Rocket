#include "Accelerometer.h"

float Accelerometer::getAverage(int axis, float buf[][3]) {
    float sum = 0;
    for (int i = 0; i < N; i++) {sum += buf[i][axis];}
    return sum / N;
}

bool Accelerometer::begin() {
    mpu.initialize();
    return mpu.testConnection();
}

bool Accelerometer::getData(float accelOut[3], float gyroOut[3]) {

    if (!mpu.testConnection()) {  // 檢查是否連接
        for (int i = 0; i < 3; i++) {
            accelOut[i] = 0.0;
            gyroOut[i] = 0.0;
        }
        return false;
    }

    int16_t accel[3];
    int16_t gyro[3];

    mpu.getAcceleration(&accel[0], &accel[1], &accel[2]);
    mpu.getRotation(&gyro[0], &gyro[1], &gyro[2]);

    for (int i = 0; i < 3; i++) {
        accel_buf[index][i] = accel[i] / 16384.0;
        gyro_buf[index][i] = gyro[i] / 131.0;
    }

    index = (index + 1) % N;  // 更新索引

    for (int i = 0; i < 3; i++) {
        accelOut[i] = getAverage(i, accel_buf);
        gyroOut[i] = getAverage(i, gyro_buf);
    }

    return true;
}