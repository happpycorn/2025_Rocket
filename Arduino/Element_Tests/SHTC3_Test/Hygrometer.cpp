#include "Hygrometer.h"

bool Hygrometer::begin() {
    return shtc3.begin();
}

bool Hygrometer::getData(float &temperature, float &humidity) {
    sensors_event_t h, t;
    bool succ = shtc3.getEvent(&h, &t);
    humidity = h.relative_humidity;  // 讀取濕度
    temperature = t.temperature;  // 讀取溫度
    return succ;
}