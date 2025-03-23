#include "ServoController.h"

ServoController::ServoController(int servoPin, int onAngle, int offAngle)
    : pin(servoPin), angleOn(onAngle), angleOff(offAngle) {}

void ServoController::begin() {
    servo.attach(pin);
    setServoAngle(false)
    Serial.print("Servo attached to pin: ");
    Serial.println(pin);
}

void ServoController::setServoAngle(bool newState) {
    isOpen = newState;
    int angle = isOpen ? angleOn : angleOff;
    servo.write(angle);
    Serial.print("Servo moved to: ");
    Serial.println(angle);
}

void ServoController::toggle() {
    setServoAngle(!isOpen);
}
