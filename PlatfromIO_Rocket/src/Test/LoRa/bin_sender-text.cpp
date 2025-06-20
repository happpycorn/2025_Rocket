#include "Constant.h"
#include "LoRaDataSender.h"

LoRaDataSender lora;

void setup() {
    Serial.begin(115200);
    Serial.println("Init...");

    if (!lora.begin()) {
        Serial.println("LoRa Init Fail.");
        while (1);
    }

    lora.println("Start!");
    Serial.println("Start!");
}

void loop() {
    lora.println("Hello World!");
    Serial.print("Sent: "); Serial.println(lora.pack_count);

    delay(1000);
}