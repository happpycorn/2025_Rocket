#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Adafruit_SHT31.h>

class Hygrometer {
public:

    Hygrometer() : shtc3() {}

    bool begin();
    bool getData(float &temperature, float &humidity);

private:

    Adafruit_SHT31 shtc3;
};

#endif  // HYGROMETER_H
