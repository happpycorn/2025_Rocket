#include "ServoController.h"

// Constructor
ServoController::ServoController(int servoPin, int onAngle, int offAngle, int channel)
    : pin(servoPin), angleOn(onAngle), angleOff(offAngle), channel(channel) {}

// 初始化 PWM 頻率與分辨率
void ServoController::begin() {
    ledcSetup(channel, 50, 16);  // 50Hz, 16-bit resolution
    ledcAttachPin(pin, channel);
    setServoAngle(false);
}

// 設定伺服角度
void ServoController::setServoAngle(bool newState) {
    isOpen = newState;
    int angle = newState ? angleOn : angleOff;
    // 將角度轉為 PWM pulse 寬度（0~65535）
    int duty = map(angle, 0, 180, 1638, 8192); // 對應 0.5ms 到 2.5ms (佔 20ms 週期)
    ledcWrite(channel, duty);
}