#include <ESP32Servo.h>

#define SERVO_PIN 25  // 伺服馬達接腳

Servo servo;  // 創建伺服物件

void setServoAngle(bool state) {
    int angle = state ? 180 : 60;  // 根據 state 設定角度
    servo.write(angle);
    Serial.print("Servo moved to: ");
    Serial.println(angle);
}

void setup() {
    Serial.begin(115200);  // 初始化串口
    servo.attach(SERVO_PIN);  // 將伺服馬達附加到腳位
    Serial.println("Press Enter to toggle between 60 and 180 degrees.");
}

void loop() {
    if (Serial.available() > 0) {
        Serial.read();  // 讀取並忽略輸入
        Serial.println("in");
        static bool state = false;  // 狀態變數
        state = !state;  // 切換狀態
        setServoAngle(state);  // 設定伺服角度
    }
    delay(100);  // 避免過度佔用處理器
}
