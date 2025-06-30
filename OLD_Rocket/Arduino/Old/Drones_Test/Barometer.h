#ifndef BAROMETER_H
#define BAROMETER_H

#include <Adafruit_BMP3XX.h>

class BMPController {
public:

    BMPController(uint8_t address, float std_pressure);

    bool begin();
    bool getData(float &temperature, float &pressure, float &altitude);

private:

    Adafruit_BMP3XX bmp;
    uint8_t i2cAddress;   // I2C 地址
    float std_pressure;
};

#endif  // BAROMETER_H
