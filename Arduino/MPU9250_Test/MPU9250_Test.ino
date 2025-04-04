#include "Accelerometer.h"

Accelerometer accel;

void setup() {
    Serial.begin(115200);
    Wire.begin(SDA_PIN, SCL_PIN);
    if (!accel.begin(&Wire)) {
        Serial.println("Could not find MPU9250");
        while (1);
    }
}

void loop() {
    float acc[3], gyro[3], mag[3], aSqrt, mD;
    if (accel.getData(acc, gyro, mag, aSqrt, mD)) {
        Serial.print("Accel: ");
        for (int i = 0; i < 3; i++) { 
            Serial.print(acc[i]); 
            Serial.print(","); 
        }
        Serial.println();
        Serial.print("Gyro: ");
        for (int i = 0; i < 3; i++) { 
            Serial.print(gyro[i]); 
            Serial.print(","); 
        }
        Serial.println();
        Serial.print("Mag: ");
        for (int i = 0; i < 3; i++) {
            Serial.print(mag[i]);
            Serial.print(",");
        }
        Serial.println();
        Serial.print("aSqrt: "); Serial.println(aSqrt);
        Serial.print("mDirection: "); Serial.println(mD);
    } else {
        Serial.println("Failed to read data");
    }
    delay(1000);
}
