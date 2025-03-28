#include "Config.h"

BMPController bmps[BMP_COUNT] = {
    BMPController(BMP_I2C_ADDRESS_1, STANDARD_PRESSURE),
    BMPController(BMP_I2C_ADDRESS_2, STANDARD_PRESSURE)
};

ServoController servos[SERVO_COUNT] = {
    ServoController(SERVO_PIN_1),
    ServoController(SERVO_PIN_2),
    ServoController(SERVO_PIN_3)
};

Accelerometer imu;  // 創建 IMU 物件

void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < BMP_COUNT; i++) { bmps[i].begin(); }

    for (int i = 0; i < SERVO_COUNT; i++) { servos[i].begin(); }

    Wire.begin();
    imu.begin();
}   

void loop() {

}