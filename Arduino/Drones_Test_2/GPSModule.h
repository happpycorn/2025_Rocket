#pragma once

#include <TinyGPS++.h>
#include <HardwareSerial.h>
#include <math.h>  // for NAN

#define GPS_UART_CHANNEL 1
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600
#define GPS_DATA_AGE_LIMIT 2000

class GPSModule{
private:
    TinyGPSPlus gps;
    HardwareSerial& serial;
    int data_addr;

public:
    GPSModule(int addr);
    bool begin();
    bool getData(double d_data[], float f_data[]);
};
