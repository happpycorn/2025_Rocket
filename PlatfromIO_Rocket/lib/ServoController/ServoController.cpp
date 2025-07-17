#include "ServoController.h"

ServoController::ServoController(int servoPin, int onAngle, int offAngle)
    : pin(servoPin), angleOn(onAngle), angleOff(offAngle) {}

void ServoController::begin() {
    myservo.attach(pin);
    Serial.println(pin);
    setServoAngle(false);
}

void ServoController::setServoAngle(bool newState) {
    isOpen = newState;
    int angle = newState ? angleOn : angleOff;
    myservo.write(angle);
    Serial.println(angle);
    Serial.println(angle);
    delay(1000);
}
