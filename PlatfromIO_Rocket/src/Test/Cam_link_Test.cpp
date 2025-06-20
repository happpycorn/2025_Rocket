#include <Arduino.h>

void setup() {
  pinMode(33, OUTPUT); // 板上 LED
}

void loop() {
  digitalWrite(33, HIGH);
  delay(500);
  digitalWrite(33, LOW);
  delay(500);
}
