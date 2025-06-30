#include <Arduino.h>
#include "Accelerometer-9250.h"

Accelerometer mpu(0);

void setup() {
    Serial.begin(115200);
    Wire.begin();

    if (!mpu.begin()) {
        Serial.println("MPU9250 初始化失敗，請確認接線！");
        while (1);
    }
}

void loop() {
    float data[12];

    if (mpu.getData(data)) {
        Serial.print(data[9]); Serial.print(",");
        Serial.print(data[10]); Serial.print(",");
        Serial.print(data[11]); Serial.println();
    }
    
    delay(10);
}
