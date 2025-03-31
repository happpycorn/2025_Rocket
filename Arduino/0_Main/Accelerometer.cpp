#include "Accelerometer.h"

bool Accelerometer::begin() {
    if (!mpu.begin()) {
        return false;
    }
    mpu.setAccelRange(MPU9250::ACCEL_RANGE_4G);
    mpu.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
    mpu.setMagnetometerRange(MPU9250::MAG_RANGE_16BIT);
    return true;
}

bool Accelerometer::getData(float &accelOut[3], float &gyroOut[3], float &magOut[3]) {
    if (!mpu.readSensor()) {
        for (int i = 0; i < 3; i++) {
            accelOut[i] = 0.0;
            gyroOut[i] = 0.0;
            magOut[i] = 0.0;
        }
        return false;
    }
    
    for (int i = 0; i < 3; i++) {
        accelOut[i] = mpu.getAccel(i);
        gyroOut[i] = mpu.getGyro(i);
        magOut[i] = mpu.getMag(i);
    }
    
    return true;
}
