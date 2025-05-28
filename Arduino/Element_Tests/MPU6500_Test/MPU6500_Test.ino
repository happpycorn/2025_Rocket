#include "Accelerometer.h"

Accelerometer accel(0);                  // data[6~16]

float sensorData[11];  // 確保足夠儲存所有欄位

void setup() {
    Serial.begin(115200);
    Wire.begin();
    delay(100);

    bool ok3 = accel.begin();

    Serial.println(ok3 ? "MPU 初始化成功" : "MPU 初始化失敗");
}

void loop() {
    Serial.println("讀取感測器資料...");

    bool accelOk = accel.getData(sensorData);

    Serial.println("---- MPU ----");
    if (accelOk) {
        Serial.print("Accel: ");
        Serial.print(sensorData[0]); Serial.print(", ");
        Serial.print(sensorData[1]); Serial.print(", ");
        Serial.print(sensorData[2]); Serial.println(" m/s^2");

        Serial.print("Gyro: ");
        Serial.print(sensorData[3]); Serial.print(", ");
        Serial.print(sensorData[4]); Serial.print(", ");
        Serial.print(sensorData[5]); Serial.println(" deg/s");

        Serial.print("Mag: ");
        Serial.print(sensorData[6]); Serial.print(", ");
        Serial.print(sensorData[7]); Serial.print(", ");
        Serial.print(sensorData[8]); Serial.println(" uT");

        Serial.print("Accel Magnitude: "); Serial.println(sensorData[9]);
        Serial.print("Mag Direction: "); Serial.println(sensorData[10]);
    } else {
        Serial.println("MPU 讀取失敗");
    }

    Serial.println("============================\n");
    delay(1000);  // 每秒讀取一次
}
