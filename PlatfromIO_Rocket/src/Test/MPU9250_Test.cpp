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
        for (int i = 9; i < 12; i++) {
            Serial.print(data[i]); 
            Serial.print(", ");
        }
        Serial.println();
    }
    
    delay(10);
}
