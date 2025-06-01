#pragma once

#include <ESP32Servo.h>

class ServoController {
public:

    ServoController(int servoPin, int onAngle = 0, int offAngle = 120);
    
    void begin();
    void setServoAngle(bool newState);

    bool isOpen;

private:

    Servo servo;
    int pin;
    int angleOn;
    int angleOff;
};
