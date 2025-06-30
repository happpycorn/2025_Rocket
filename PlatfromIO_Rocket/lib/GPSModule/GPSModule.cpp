#include "GPSModule.h"

GPSModule::GPSModule(int addr)
    : serial(HardwareSerial(GPS_UART_CHANNEL)), data_addr(addr) {}

bool GPSModule::begin() {
    serial.begin(GPS_BAUD, SERIAL_8N1, GPS_RX_PIN, GPS_TX_PIN);
    return true;
}

bool GPSModule::getData(double d_data[], float f_data[]) {
    while (serial.available() > 0) {
        gps.encode(serial.read());
    }

    if (!gps.location.isValid() || gps.location.age() >= GPS_DATA_AGE_LIMIT) {

        d_data[0] = NAN;
        d_data[1] = NAN;
        for (int i = 0; i < 11; i++) { f_data[data_addr + i] = NAN; }

        return false;
    }

    d_data[0] = gps.location.lat();
    d_data[1] = gps.location.lng();

    f_data[data_addr+0] = gps.altitude.meters();
    f_data[data_addr+1] = gps.speed.kmph();
    f_data[data_addr+2] = gps.course.deg();
    
    f_data[data_addr+3] = gps.time.hour();
    f_data[data_addr+4] = gps.time.minute();
    f_data[data_addr+5] = gps.time.second();
    f_data[data_addr+6] = gps.date.day();
    f_data[data_addr+7] = gps.date.month();
    f_data[data_addr+8] = gps.date.year();

    f_data[data_addr+9] = gps.hdop.hdop();
    f_data[data_addr+10] = gps.satellites.value();
        
    return true;
}