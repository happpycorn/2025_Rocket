#include "Config.h"

void setup() {
    Serial.begin(115200);         // 給電腦看的 Serial
}

void loop() {
    if (LoRa.available()) {
        String received = LoRa.readStringUntil('\n');
        Serial.print("Received: ");
        Serial.println(received);
    }
}
