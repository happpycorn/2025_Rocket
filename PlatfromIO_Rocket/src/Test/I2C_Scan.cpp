#include "Constant.h"
#include <Wire.h>

void setup() {
    Serial.begin(115200);
    Wire.begin();

    Serial.println("I2C 掃描器開始...");
    
    for (byte i = 8; i < 120; i++) {
        Wire.beginTransmission(i);
        byte error = Wire.endTransmission();
        if (error == 0) {
            Serial.print("設備發現: 0x");
            Serial.println(i, HEX);
        }
    }

    Serial.println("I2C 掃描完成!");

    Serial.println("各感測器編號");
    Serial.print("BMP390-1: "); Serial.println(BMP_I2C_ADDRESS_1, HEX);
    Serial.print("BMP390-2: "); Serial.println(BMP_I2C_ADDRESS_2, HEX);
    Serial.print("MPU6500: ");  Serial.println(0x68, HEX);
    Serial.print("MPU9250: "); Serial.println(0x68, HEX);
    Serial.print("SHTC3: ");   Serial.println(0x70, HEX);
}

void loop() {}
