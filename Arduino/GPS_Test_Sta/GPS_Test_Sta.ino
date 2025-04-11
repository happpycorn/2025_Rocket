#include <TinyGPSPlus.h>
#include <HardwareSerial.h>
#include <SPI.h>
#include <SD.h>

TinyGPSPlus gps;
HardwareSerial SerialGPS(2); // UART2：GPIO16 (RX2), GPIO17 (TX2)
File logFile;

const int chipSelect = 5; // SD 卡 CS 腳，根據你的模組調整

void setup() {
  Serial.begin(115200);
  SerialGPS.begin(9600, SERIAL_8N1, 16, 17);
  Serial.println("啟動 GPS 測試...");

  if (!SD.begin(chipSelect)) {
    Serial.println("SD 卡初始化失敗！");
    while (true); // 停住，因為無法寫入
  }

  // 檢查是否有 log 檔，沒有就建立並寫入標頭
  if (!SD.exists("/gps_log.csv")) {
    logFile = SD.open("/gps_log.csv", FILE_WRITE);
    if (logFile) {
      logFile.println("Time,Latitude,Longitude,Speed(km/h),Altitude(m)");
      logFile.close();
    }
  }
}

void loop() {
  while (SerialGPS.available()) {
    gps.encode(SerialGPS.read());
  }

  if (gps.location.isUpdated()) {
    double lat = gps.location.lat();
    double lng = gps.location.lng();
    double speed = gps.speed.kmph();
    double alt = gps.altitude.meters();
    int h = gps.time.hour();
    int m = gps.time.minute();
    int s = gps.time.second();

    // 顯示到序列監視器
    Serial.print("緯度: "); Serial.println(lat, 6);
    Serial.print("經度: "); Serial.println(lng, 6);
    Serial.print("速度(km/h): "); Serial.println(speed);
    Serial.print("高度(m): "); Serial.println(alt);
    Serial.print("時間: "); 
    Serial.print(h); Serial.print(":");
    Serial.print(m); Serial.print(":");
    Serial.println(s);
    Serial.println("---------------------------");

    // 儲存到 SD 卡
    logFile = SD.open("/gps_log.csv", FILE_APPEND);
    if (logFile) {
      logFile.print(h); logFile.print(":");
      logFile.print(m); logFile.print(":");
      logFile.print(s); logFile.print(",");
      logFile.print(lat, 6); logFile.print(",");
      logFile.print(lng, 6); logFile.print(",");
      logFile.print(speed); logFile.print(",");
      logFile.println(alt);
      logFile.close();
    } else {
      Serial.println("無法寫入 SD 卡！");
    }
  }
}
