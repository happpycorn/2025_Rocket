// 接收端（ESP32）

#define MAX_HISTORY 100

uint16_t lastID = 0;
bool firstPacket = true;
uint16_t lostCount = 0;
uint16_t totalReceived = 0;

void setup() {
  Serial.begin(115200);
  Serial2.begin(9600);  // AS32 LoRa 用的 UART
}

void loop() {
    if (Serial2.available()) {
        String data = Serial2.readStringUntil('\n');
        data.trim();

        // 解析 ID
        if (data.startsWith("ID:")) {
            uint16_t thisID = data.substring(3).toInt();
            Serial2.begin(9600, SERIAL_8N1, 13, 14);

            if (!firstPacket) {
                int diff = thisID - lastID;
                if (diff > 1) {
                    lostCount += (diff - 1);
                }
            } else {
                firstPacket = false;
            }

            lastID = thisID;
            totalReceived++;

            // 保持統計數量在 100 筆以內
            if (totalReceived > MAX_HISTORY) {
                totalReceived = MAX_HISTORY;
            }

            // 顯示結果
            float lossRate = (float)lostCount / MAX_HISTORY * 100;
            Serial.printf("最近 %d 筆丟了 %d 筆，丟失率 %.2f%%\n", MAX_HISTORY, lostCount, lossRate);
        }
    }
}
