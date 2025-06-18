#include "LoRaDataReciver.h"

LoRaDataReciver lora;

void setup() {
    Serial.begin(115200);
    lora.begin();  // 初始化 UART
    Serial.println("LoRa receiver started.");
}

void loop() {
    auto result = lora.reciveData();

    if (result.is_message) {
        Serial.print("[文字] 收到訊息：");
        Serial.println(result.message);
    }

    if (result.data.is_data) {
        Serial.println("[二進位] ✅ 收到封包");
        Serial.print("封包編號：");
        Serial.println(result.data.pack_count);

        // 印出 float
        for (int i = 0; i < RECIVE_FLOAT_DATA_LEN; i++) {
            Serial.print("Float[");
            Serial.print(i);
            Serial.print("] = ");
            Serial.println(result.data.f[i], 6);
        }

        // 印出 bool
        for (int i = 0; i < RECIVE_BOOL_DATA_LEN; i++) {
            Serial.print("Bool[");
            Serial.print(i);
            Serial.print("] = ");
            Serial.println(result.data.b[i] ? "true" : "false");
        }

        // 印出 double
        for (int i = 0; i < 2; i++) {
            Serial.print("Double[");
            Serial.print(i);
            Serial.print("] = ");
            Serial.println(result.data.d[i], 6);
        }

        Serial.println("------------------------------------------------");
    }

    delay(10);  // 小延遲避免佔用太多處理時間
}
