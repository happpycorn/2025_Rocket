#define RXD2 14  // 接收腳位
#define TXD2 13  // 傳送腳位
#define M0_PIN 22  // 連接 M0 的 GPIO 引腳
#define M1_PIN 23  // 連接 M1 的 GPIO 引腳

void setup() {
    Serial.begin(115200);                // 用來 debug 的串口
    Serial2.begin(9600, SERIAL_8N1, RXD2, TXD2); // LoRa 模組（波特率依據數據手冊，可調整）

    pinMode(M0_PIN, OUTPUT);         // 設置 M0 控制引腳為輸出
    pinMode(M1_PIN, OUTPUT);         // 設置 M1 控制引腳為輸出

    // 進入配置模式
    digitalWrite(M0_PIN, HIGH);      // 設定 M0 高電位
    digitalWrite(M1_PIN, HIGH);      // 設定 M1 高電位

    delay(500);  // 等待配置模式啟動
    Serial.println("LoRa Configuration Mode");
}

void loop() {
    // 發送查詢版本的命令（以數據手冊中定義為例）
    byte versionCmd[] = { 0xC1, 0xC1, 0xC1 }; 
    Serial2.write(versionCmd, sizeof(versionCmd));
    delay(3000);  // 等待回應

    // 讀取回應（以十六進位方式顯示）
    while (Serial2.available()) {
        byte incoming = Serial2.read();
        Serial.print("0x");
        if(incoming < 0x10) Serial.print("0"); // 補零
        Serial.print(incoming, HEX);
        Serial.print(" ");
    }
    Serial.println();
}
