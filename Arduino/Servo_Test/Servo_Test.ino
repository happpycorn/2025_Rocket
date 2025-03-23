#include <ESP32Servo.h>

class ServoController {
private:

    Servo servo;
    int pin;
    int angleOn;
    int angleOff;
    bool isOpen = false;

public:
    // 建構函式，初始化伺服馬達
    ServoController(int servoPin, int onAngle = 0, int offAngle = 120)
        : pin(servoPin), angleOn(onAngle), angleOff(offAngle) {}

    // 初始化伺服
    void begin() {
        servo.attach(pin);
        Serial.print("Servo attached to pin: ");
        Serial.println(pin);
    }

    // 設定伺服角度
    void setServoAngle(bool newState) {
        isOpen = newState;
        int angle = isOpen ? angleOn : angleOff;
        servo.write(angle);
        Serial.print("Servo is ");
        Serial.println(isOpen ? "open" : "close");
    }

    // 切換狀態
    void toggle() {
        setServoAngle(!isOpen);
    }
};

#define SERVO_PIN 25  // 你的伺服馬達腳位

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
