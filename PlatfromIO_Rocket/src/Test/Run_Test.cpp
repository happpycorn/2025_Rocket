#include "Arduino.h"

int i = 0;

void setup() {
    Serial.begin(115200);
}

void loop() {
    Serial.println(i++);
    delay(1000);
}