#include "Accelerometer-9250.h"

bool Accelerometer::begin() {

    Serial.println("進入 begin()");
    bool result = mpu.setup(0x68);
    Serial.print("setup 結果: "); Serial.println(result);

    Serial.println("準備 return true");
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

    data[data_addr+9] = mpu.getRoll();
    data[data_addr+10] = mpu.getPitch();
    data[data_addr+11] = mpu.getYaw();

    return true;
}
