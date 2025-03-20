#include <Wire.h>

void setup() {
  Serial.begin(115200);
  Wire.begin();

  Serial.println("I2C 掃描器開始...");
  
  for (byte i = 8; i < 120; i++) {
    Wire.beginTransmission(i);
    byte error = Wire.endTransmission();
    if (error == 0) {
      Serial.print("設備發現: 0x");
      Serial.println(i, HEX);
    }
  }

  Serial.println("I2C 掃描完成!");
}

void loop() {
  // 無需在 loop 中執行任何操作
}
