#include "GPSModule.h"

// 解析 NMEA 字符串
void GPSModule::parseNMEA(String nmea, GPSData* gps) {
    if (nmea.startsWith("$GPGGA")) {  // 解析 GGA (位置/高度)
        char *data = strdup(nmea.c_str());
        char *token = strtok(data, ",");
        int field = 0;
        while (token != NULL) {
            switch (field) {
                case 1: gps->utcTime = atof(token); break;  // UTC 時間
                case 2: gps->latitude = atof(token); break; // 緯度
                case 3: if (token[0] == 'S') gps->latitude = -gps->latitude; break;
                case 4: gps->longitude = atof(token); break; // 經度
                case 5: if (token[0] == 'W') gps->longitude = -gps->longitude; break;
                case 9: gps->altitude = atof(token); break; // 高度
                case 10: gps->geoidSeparation = atof(token); break; // 大地水準面高度
                case 7: gps->numSatellites = atoi(token); break; // 衛星數
            }
            token = strtok(NULL, ",");
            field++;
        }
        free(data);
    } else if (nmea.startsWith("$GNRMC")) { // 解析 RMC (時間/速度/航向)
        char *data = strdup(nmea.c_str());
        char *token = strtok(data, ",");
        int field = 0;
        while (token != NULL) {
            switch (field) {
                case 1: gps->utcTime = atof(token); break;
                case 7: gps->groundSpeed = atof(token) * 0.51444; break; // 轉換為 m/s
                case 8: gps->heading = atof(token); break;
            }
            token = strtok(NULL, ",");
            field++;
        }
        free(data);
    } else if (nmea.startsWith("$GPGSV")) { // 解析 GSV (衛星訊號品質)
        char *data = strdup(nmea.c_str());
        char *token = strtok(data, ",");
        int field = 0;
        while (token != NULL) {
            switch (field) {
                case 3: gps->numVisibleSat = atoi(token); break; // 可見衛星數
                case 4: gps->signalQuality = atoi(token); break; // 訊號強度
            }
            token = strtok(NULL, ",");
            field++;
        }
        free(data);
    } else if (nmea.startsWith("$GPGSA")) { // 解析 GSA (精度指標)
        char *data = strdup(nmea.c_str());
        char *token = strtok(data, ",");
        int field = 0;
        while (token != NULL) {
            switch (field) {
                case 15: gps->hdop = atof(token); break; // 水平精度 (HDOP)
                case 16: gps->pdop = atof(token); break; // 3D 精度 (PDOP)
            }
            token = strtok(NULL, ",");
            field++;
        }
        free(data);
    }
}

// 讀取 GPS 串口數據
void GPSModule::readGPS(GPSData* gps) {
    while (gpsSerial.available()) {
        String nmea = gpsSerial.readStringUntil('\n');
        parseNMEA(nmea, gps);
    }
}

bool GPSModule::begin() {
    // 檢查是否能初始化 gpsSerial 並設置波特率與串口模式
    gpsSerial.begin(baundrate, module, rxp, txp);
    
    if (!gpsSerial) {
        Serial.println("❌ GPS 初始化失敗...");
        return false;
    } else {
        Serial.println("🚀 GPS 初始化成功...");
        return true;
    }
}