#include "Accelerometer.h"
#include "ServoController.h"

#define SERVO_PIN_1 26  // 你的伺服馬達腳位
#define SERVO_PIN_2 25  // 你的伺服馬達腳位
#define SERVO_PIN_3 33  // 你的伺服馬達腳位

ServoController servos[] = {
    ServoController(SERVO_PIN_1),
    ServoController(SERVO_PIN_2),
    ServoController(SERVO_PIN_3)
};

Accelerometer imu;  // 創建 IMU 物件

void setup() {
    Serial.begin(115200);
    
    for (int i = 0; i < 3; i++) {
        servos[i].begin();
    }

    Wire.begin();
    imu.begin();
}   

void loop() {

}