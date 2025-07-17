#include "Config.h"

bool iicScan();
void findiic(byte i, bool checklist[]);

void setup() {
    Serial.begin(115200);
    Wire.begin();

    bool isiicSuccess = iicScan();
    Serial.println(isiicSuccess ? 
        "iic sensor is connected" : 
        "iic sensor is fail to connect"
    );
}

void loop() {
    
}

bool iicScan() {
    Serial.println("Start iic Scan");
    bool checklist[4] = {false};
    for (byte i = 8; i < 120; i++) findiic(i, checklist);
    for (bool i : checklist) if (!i) return false;
    return true;
}

void findiic(byte i, bool checklist[]) {
    Wire.beginTransmission(i);
    byte error = Wire.endTransmission();
    if (error != 0) return;

    Serial.print("Find: 0x");
    Serial.println(i, HEX);

    switch (i) {
    case BMP_I2C_ADDRESS_1:
        Serial.println("BMP390 1 Find");
        checklist[0] = true;
        break;

    case BMP_I2C_ADDRESS_2:
        Serial.println("BMP390 2 Find");
        checklist[1] = true;
        break;

    case 0x70:
        Serial.println("SHTC3 Find");
        checklist[2] = true;
        break;

    case 0x68:
        Serial.println("MPU9250 Find");
        checklist[3] = true;
        break;

    default:
        break;
    }
}