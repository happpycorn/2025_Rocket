#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <HardwareSerial.h>

struct GPSData {
    // 位置資訊
    double latitude;      // 緯度 (°)
    double longitude;     // 經度 (°)
    float altitude;       // 高度（相對海平面, m）
    float geoidSeparation; // 大地水準面高度 (m)

    // 時間資訊
    uint32_t utcTime;     // UTC 時間（毫秒級）

    // 速度與運動方向
    float groundSpeed;    // 地面速度 (m/s)
    float heading;        // 航向角 (°)

    // 衛星訊號品質
    uint8_t numSatellites; // 已連接衛星數
    uint8_t numVisibleSat; // 可見衛星數
    uint8_t signalQuality; // 訊號強度

    // 精度指標
    float hdop;           // 水平精度指標 (HDOP)
    float pdop;           // 3D 位置精度指標 (PDOP)
};

class GPSModule {
private:

    void parseNMEA(String nmea, GPSData* gps);

    int baundrate;          // 設定串口速率（bps）
    SerialConfig module;   // 設定串口類型（UART/RS485）
    int rxp;              // RX 端口
    int txp;              // TX 端口

    HardwareSerial gpsSerial;

public:

    GPSModule(int baud, SerialConfig module, int rxp, int txp) 
        : baundrate(baud), module(module), rxp(rxp), txp(txp), gpsSerial(2) {};

    bool begin();
    void readGPS(GPSData* gps);
};

#endif // GPS_MODULE_H
