#include "ServoController.h"

#define SERVO_PIN 25

ServoController myServo(SERVO_PIN);

void setup() {
    Serial.begin(115200);
    myServo.begin();
    Serial.println("Press Enter to toggle between 60 and 180 degrees.");
}

void loop() {
    if (Serial.available() > 0) {
        Serial.read();  // 讀取並忽略輸入
        Serial.println("in");
        myServo.toggle();  // 切換伺服狀態
    }
    delay(100);
}
