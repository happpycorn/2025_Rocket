#ifndef HYGROMETER_H
#define HYGROMETER_H

#include <Adafruit_SHTC3.h>

class Hygrometer {
public:

    Hygrometer() : shtc3() {}

    bool begin();
    bool getData(float &temperature, float &humidity);

private:

    Adafruit_SHTC3 shtc3 = Adafruit_SHTC3();
};

#endif  // HYGROMETER_H
