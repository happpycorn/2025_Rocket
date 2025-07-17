#include "Config.h"

GPSData gps_d = {0};
GPSModule gpsModule(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

void setup() {
    Serial.begin(115200);  // 初始化串口通信
    Serial.println("程式開始！");

    if (!SD.begin(SD_CS)) {
        Serial.println("SD 卡初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    gpsModule.begin();

    Serial.println("初始化成功！");
}

void loop() {

    unsigned long long now = millis();

    gpsModule.readGPS(&gps_d);

    File dataFile = SD.open("/data.csv", FILE_APPEND);
    if (dataFile) {

        dataFile.print(now); dataFile.print(",");
        
        // GPS
        dataFile.print(gps_d.latitude); dataFile.print(",");
        dataFile.print(gps_d.longitude); dataFile.print(",");
        dataFile.print(gps_d.numSatellites); dataFile.print(",");
        dataFile.print(gps_d.numVisibleSat); dataFile.print(",");
        dataFile.print(gps_d.altitude); dataFile.print(",");
        dataFile.print(gps_d.geoidSeparation); dataFile.print(",");
        dataFile.print(gps_d.groundSpeed); dataFile.print(",");
        dataFile.print(gps_d.heading); dataFile.print(",");
        dataFile.print(gps_d.hdop); dataFile.print(",");
        dataFile.print(gps_d.pdop); dataFile.print(",");
        dataFile.print(gps_d.signalQuality); dataFile.print(",");
        dataFile.println(gps_d.utcTime);

        dataFile.close();
    } else {
        Serial.println("無法寫入 SD 卡");
    }

    delay(100);
}
