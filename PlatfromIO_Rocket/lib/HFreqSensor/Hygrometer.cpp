#include "Hygrometer.h"

bool Hygrometer::begin() {
    return shtc3.begin();
}

bool Hygrometer::getData(float data[]) {
    sensors_event_t h, t;
    bool succ = shtc3.getEvent(&h, &t);
    data[data_addr] = h.relative_humidity;  // 讀取濕度
    data[data_addr+1] = t.temperature;  // 讀取溫度
    return succ;
}
