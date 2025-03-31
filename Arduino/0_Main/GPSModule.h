#ifndef GPSMODULE_H
#define GPSMODULE_H

#include <HardwareSerial.h>
#include "0_Config.h"

class GPSModule {
private:

    void parseNMEA(String nmea, GPSData* gps);

    int baundrate;          // 設定串口速率（bps）
    SerialConfig module;    // 設定串口類型（UART/RS485）
    int rxp;                // RX 端口
    int txp;                // TX 端口

    HardwareSerial gpsSerial;

public:

    GPSModule(int baud, SerialConfig module, int rxp, int txp) 
        : baundrate(baud), module(module), rxp(rxp), txp(txp), gpsSerial(2) {};

    bool begin();
    void readGPS(GPSData* gps);
};

#endif // GPS_MODULE_H
