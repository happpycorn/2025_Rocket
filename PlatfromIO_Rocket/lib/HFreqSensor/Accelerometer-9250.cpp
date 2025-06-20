#include "Accelerometer-9250.h"

bool Accelerometer::begin() {
    Wire.begin();  // SDA: GPIO21, SCL: GPIO22 (ESP32 預設)

    if (!mpu.setup(0x68)) {
        return false;
    }

    // 初始化 Madgwick 濾波器（更新頻率 100Hz）
    filter.begin(100);
    
    return true;
}


bool Accelerometer::getData(float data[]) {
    if (!mpu.update()) {
        return false;
    }

    // 讀取加速度
    data[data_addr+0] = mpu.getAccX();
    data[data_addr+1] = mpu.getAccY();
    data[data_addr+2] = mpu.getAccZ();

    // 讀取陀螺儀（角速度轉為 radians/sec）
    data[data_addr+3] = radians(mpu.getGyroX());
    data[data_addr+4] = radians(mpu.getGyroY());
    data[data_addr+5] = radians(mpu.getGyroZ());

    // 讀取磁力計
    data[data_addr+6] = mpu.getMagX();
    data[data_addr+7] = mpu.getMagY();
    data[data_addr+8] = mpu.getMagZ();

    // 傳入 Madgwick 濾波器（有用磁力計 → 可得 Yaw）
    filter.update(
        data[data_addr+0], data[data_addr+1], data[data_addr+2],
        data[data_addr+3], data[data_addr+4], data[data_addr+5],
        data[data_addr+6], data[data_addr+7], data[data_addr+8]
    );

    data[data_addr+9] = filter.getRoll();
    data[data_addr+10] = filter.getPitch();
    data[data_addr+11] = filter.getYaw();

    return true;
}
