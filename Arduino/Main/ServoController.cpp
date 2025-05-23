#include "ServoController.h"

ServoController::ServoController(int servoPin, int onAngle, int offAngle)
    : pin(servoPin), angleOn(onAngle), angleOff(offAngle) {}

void ServoController::begin() {
    servo.attach(pin);
    setServoAngle(false);
}

void ServoController::setServoAngle(bool newState) {
    isOpen = newState;
    int angle = newState ? angleOn : angleOff;
    servo.write(angle);
}
