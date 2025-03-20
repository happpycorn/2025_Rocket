#include "Accelerometer.h"

Accelerometer imu;  // 創建 IMU 物件

void setup() {
    Serial.begin(115200);
    Wire.begin();

    if (!imu.begin()) {
        Serial.println("MPU6050 初始化失敗！");
        while (1);  // 停止執行
    }
}

void loop() {
    float accel[3], gyro[3];

    imu.getData(accel, gyro);

    Serial.printf("Accel (g)  : X=%+6.2f, Y=%+6.2f, Z=%+6.2f\n", accel[0], accel[1], accel[2]);
    Serial.printf("Gyro (°/s) : X=%+6.2f, Y=%+6.2f, Z=%+6.2f\n", gyro[0], gyro[1], gyro[2]);

    delay(100);
}