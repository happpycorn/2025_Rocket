#include "GPSModule.h"

// 使用 ESP32 的 UART2 (GPIO 16 = RX, GPIO 17 = TX)
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600

// 初始化 GPS 數據
GPSData gps_d = {0};

GPSModule gpsModule(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);

// 設置 ESP32
void setup() {
    Serial.begin(115200);
    gpsModule.begin();
    Serial.println("🚀 GPS 初始化完成...");
}

// 主循環
void loop() {
    gpsModule.readGPS(&gps_d);

    // 打印 GPS 數據
    Serial.printf("📍 經緯度: %.6f, %.6f\n", gps_d.latitude, gps_d.longitude);
    Serial.printf("🛰 衛星數: %d (可見: %d)\n", gps_d.numSatellites, gps_d.numVisibleSat);
    Serial.printf("📏 高度: %.2f m (大地水準面: %.2f m)\n", gps_d.altitude, gps_d.geoidSeparation);
    Serial.printf("🚀 地面速度: %.2f m/s\n", gps_d.groundSpeed);
    Serial.printf("🧭 航向: %.2f°\n", gps_d.heading);
    Serial.printf("📊 HDOP: %.2f, PDOP: %.2f\n", gps_d.hdop, gps_d.pdop);
    Serial.printf("📡 訊號強度: %d\n", gps_d.signalQuality);
    Serial.printf("⏰ UTC 時間: %06d\n", gps_d.utcTime);
    
    delay(1000);  // 1Hz 更新
}
