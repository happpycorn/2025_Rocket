#pragma once

#include "Constant.h"

class ServoController {
public:
    ServoController(int servoPin, int onAngle, int offAngle, int channel);

    void begin();
    void setServoAngle(bool newState);

    bool isOpen = false;

private:
    int pin;
    int angleOn;
    int angleOff;
    int channel;
};
