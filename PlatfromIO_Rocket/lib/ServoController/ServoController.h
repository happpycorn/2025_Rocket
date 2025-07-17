#pragma once

#include "Constant.h"

class ServoController {
public:
    ServoController(int servoPin, int onAngle, int offAngle);

    void begin();
    void setServoAngle(bool newState);

private:
    int pin;
    int angleOn;
    int angleOff;
    bool isOpen = false;
    int channel = 0;
};
