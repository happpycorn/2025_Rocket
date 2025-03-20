#include <HardwareSerial.h>

HardwareSerial mySerial(1);  // 使用 Serial1

// $GPRMC,074238.00,A,2501.09610,N,12132.95100,E,0.357,,100225,,,A*79
// $GPVTG,,T,,M,0.357,N,0.661,K,A*23
// $GPGGA,074238.00,2501.09610,N,12132.95100,E,1,04,2.79,45.9,M,17.1,M,,*67
// $GPGSA,A,3,02,03,01,14,,,,,,,,,5.57,2.79,4.82*02
// $GPGSV,1,1,04,01,60,034,30,02,51,029,29,03,39,128,26,14,46,326,26*7A
// $GPGLL,2501.09610,N,12132.95100,E,074238.00,A,A*65

void setup() {
  // 初始化串口監控
  Serial.begin(115200);
  // 初始化 GPS 模組的串口（使用 ESP32 的 Serial1）
  mySerial.begin(9600, SERIAL_8N1, 16, 17); // RX 是 GPIO 16, TX 是 GPIO 17

  Serial.println("GPS 測試開始...");
}

void loop() {
  // 當 GPS 模組有數據時
  while (mySerial.available()) {
    char c = mySerial.read(); // 讀取一個字元
    Serial.print(c); // 輸出到串口監控
  }
}
