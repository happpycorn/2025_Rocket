#include <Arduino.h>
#include <Wire.h>

void setup() {
    Serial.begin(9600);
    delay(2000);
    Serial.println("Start");

    for (int sda = 0; sda <= 22; sda++) {
        for (int scl = 0; scl <= 22; scl++) {
            if (sda == scl) continue; // Skip same-pin pair

            Wire.begin(sda, scl);
            delay(50);  // Small delay to stabilize

            for (byte addr = 8; addr < 120; addr++) {
                Wire.beginTransmission(addr);
                if (Wire.endTransmission() == 0) {
                    Serial.printf("%d, %d, 0x%02X\n", sda, scl, addr);
                }
            }

            Wire.end();  // Clean up for next combination
        }
    }

    Serial.println("Complete");
}

void loop() {}
