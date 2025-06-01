#include "Accelerometer.h"

bool Accelerometer::begin(TwoWire* wire) {
    mpu.setWire(wire);

    mpu.beginAccel();
    mpu.beginGyro();
    mpu.beginMag();

    // You can set your own offset for mag values
    // mpu.magXOffset = -50;
    // mpu.magYOffset = -55;
    // mpu.magZOffset = -10;

    return true;
}

bool Accelerometer::getData(float *accelOut, float *gyroOut, float *magOut, float &aSqrt, float &mDirection) {

    uint8_t sensorId;
    int result;

    result = mpu.readId(&sensorId);
    if (result != 0) {
        for (int i = 0; i < 3; i++) {
            accelOut[i] = 0.0;
            gyroOut[i] = 0.0;
            magOut[i] = 0.0;
        }
        return false;
    }

    bool success = true;

    // 加速度
    result = mpu.accelUpdate();
    if (result == 0) {
        accelOut[0] = mpu.accelX();
        accelOut[1] = mpu.accelY();
        accelOut[2] = mpu.accelZ();
        aSqrt = mpu.accelSqrt();
    } else {
        for (int i = 0; i < 3; i++) { accelOut[i] = 0.0; }
        success = false;
    }

    // 角速度
    result = mpu.gyroUpdate();
    if (result == 0) {
        gyroOut[0] = mpu.gyroX();
        gyroOut[1] = mpu.gyroY();
        gyroOut[2] = mpu.gyroZ();
    } else {
        for (int i = 0; i < 3; i++) { gyroOut[i] = 0.0; }
        success = false;
    }

    // 磁力計
    result = mpu.magUpdate();
    if (result != 0) {
        mpu.beginMag();
        result = mpu.magUpdate();
    }
    if (result == 0) {
        magOut[0] = mpu.magX();
        magOut[1] = mpu.magY();
        magOut[2] = mpu.magZ();
        mDirection = mpu.magHorizDirection();
    } else {
        for (int i = 0; i < 3; i++) { magOut[i] = 0.0; }
        success = false;
    }

    return success;
}
