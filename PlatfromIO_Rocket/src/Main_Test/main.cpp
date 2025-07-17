#include "Config.h"

void getPressure();
bool iicScan();
void findiic(byte i, bool checklist[]);

ServoController* servos[SERVO_COUNT] = {
    new ServoController(SERVO_PIN_1, 120, 0),
    new ServoController(SERVO_PIN_2, 120, 0),
    new ServoController(SERVO_PIN_3, 120, 0)
};

String inputString = "";

void setup() {
    Serial.begin(115200);
    Wire.begin();

    bool isiicSuccess = iicScan();
    Serial.println(isiicSuccess ? 
        "iic sensor is connected" : 
        "iic sensor is fail to connect"
    );

    if (isiicSuccess) getPressure();
    
    for (int i = 0; i < SERVO_COUNT; i++) { servos[i]->begin(); }

    Serial.println("Input servo number + bool to control servo.");
    Serial.println("Like 00 or 21 or 10.");
}

void loop() {
    while (Serial.available()) {
        char c = Serial.read();

        if (c != '\n' && c != '\r') {
            inputString += c;
            continue;
        }

        inputString.trim();

        if (inputString == "00") servos[0]->setServoAngle(false);
        else if (inputString == "01") servos[0]->setServoAngle(true);
        else if (inputString == "10") servos[1]->setServoAngle(false);
        else if (inputString == "11") servos[1]->setServoAngle(true);
        else if (inputString == "20") servos[2]->setServoAngle(false);
        else if (inputString == "21") servos[2]->setServoAngle(true);
        else Serial.println("Unknow input");

        for (int i = 0; i < 3; i++) Serial.print(servos[i]->isOpen);
        Serial.println();

        inputString = "";
    }
}

void getPressure() {
    Serial.println("Trying to get pressure");

    const float STANDARD_PRESSURE = 1013.25;
    float data[6];
    BMPController bmp1(BMP_I2C_ADDRESS_1, STANDARD_PRESSURE, 0);
    BMPController bmp2(BMP_I2C_ADDRESS_2, STANDARD_PRESSURE, 3);
    bmp1.begin();
    bmp2.begin();

    float sum_pressure_1 = 0;
    float sum_pressure_2 = 0;
    int loop_time = 100;
    for (int i = 0; i < loop_time; i++) {
        bmp1.getData(data);
        bmp2.getData(data);
        sum_pressure_1 += data[1];
        sum_pressure_2 += data[4];
    }

    Serial.print("Bmp 1 pressure: ");
    Serial.println(sum_pressure_1/loop_time);
    Serial.print("Bmp 2 pressure: ");
    Serial.println(sum_pressure_2/loop_time);
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