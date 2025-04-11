#ifndef SERVO_CONTROLLER_H
#define SERVO_CONTROLLER_H

#include <ESP32Servo.h>

class ServoController {
public:

    ServoController(int servoPin, int onAngle = 0, int offAngle = 120);
    
    void begin();
    void setServoAngle(bool newState);
    void toggle();
    bool isOpen = false;

private:

    Servo servo;
    int pin;
    int angleOn;
    int angleOff;
};

#endif  // SERVO_CONTROLLER_H
