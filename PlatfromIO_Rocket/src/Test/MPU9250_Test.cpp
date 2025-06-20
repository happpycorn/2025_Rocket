#include <Arduino.h>
#include "Accelerometer-9250.h"

Accelerometer mpu(0);

unsigned long lastUpdate = 0;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);

    Wire.beginTransmission(0x68);
    Wire.write(0x75);  // WHO_AM_I register
    Wire.endTransmission(false);
    Wire.requestFrom(0x68, 1);
    uint8_t whoami = Wire.read();
    Serial.print("WHO_AM_I = 0x"); Serial.println(whoami, HEX);

    delay(1000);

    if (!mpu.begin()) {
        Serial.println("MPU9250 初始化失敗，請確認接線！");
        while (1);
    }
}

void loop() {
    if (millis() - lastUpdate >= 10) {  // 每 10ms 更新一次 (100Hz)
        lastUpdate = millis();

        float data[12];

        if (mpu.getData(data)) {
            for (int i = 0; i < 12; i++) Serial.print(data[i]); Serial.print(", ");
            Serial.println();
        }
    }
}
