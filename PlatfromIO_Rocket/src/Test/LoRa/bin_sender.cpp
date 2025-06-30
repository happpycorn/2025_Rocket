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
    float f[21] = {
        0, 0, 0,
        0, 0, 0,
        123.45, 567.89, 543.21,
        0, 0, 0,
        0, 0, 0,
        0, 0, 0,
        123.45, 567.89, 543.21,
    };
    bool b[11] = {0, 1, 1, 0, 1, 0, 0, 1, 1, 0, 1};
    double d[2] = {789.12, 345.67};

    lora.sendData(f, b, d);
    Serial.print("Sent: "); Serial.println(lora.pack_count);

    delay(1000);
}