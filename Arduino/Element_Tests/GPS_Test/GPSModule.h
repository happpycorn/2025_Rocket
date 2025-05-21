#pragma once

#include <math.h>  // for NAN
#include <TinyGPSPlus.h>
#include <HardwareSerial.h>

#define GPS_UART_CHANNEL 2        // UART2
#define GPS_RX_PIN 16             // RX pin (根據你的接法調整)
#define GPS_TX_PIN 17             // TX pin (根據你的接法調整)
#define GPS_BAUD 9600             // GPS 預設的 Baudrate
#define GPS_DATA_AGE_LIMIT 2000   // 允許資料的最大時間（ms）

class GPSModule{
private:
    TinyGPSPlus gps;
    HardwareSerial serial;
    int data_addr;

public:
    GPSModule(int addr);
    bool begin();
    bool getData(double d_data[], float f_data[]);
};
