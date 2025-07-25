#include <Arduino.h>
#include <Wire.h>

void setup() {
    Serial.begin(115200);
    Wire.begin(21, 22);  // 改成你的 SDA / SCL 腳位
    delay(100);

    Serial.println("Scanning I2C...");

    for (byte addr = 8; addr < 120; addr++) {
        Wire.beginTransmission(addr);
        if (Wire.endTransmission() == 0) {
            Serial.printf("Found device at 0x%02X\n", addr);
        }
    }

    Serial.println("Done.");
}

void loop() {}
