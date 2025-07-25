#pragma once

#include "Constant.h"

class ServoController {
public:
    ServoController(ServoSetting servos_setting);

    void begin();
    void setServoAngle(bool newState);

    bool isOpen = false;

private:
    int pin;
    int angleOn;
    int angleOff;
    int channel;
};
