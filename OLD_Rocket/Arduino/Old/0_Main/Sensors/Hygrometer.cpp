#include "Hygrometer.h"

bool Hygrometer::begin() {
    return shtc3.begin();
}

bool Hygrometer::getData(float &temperature, float &humidity) {
    temperature = shtc3.readTemperature();  // 讀取溫度
    humidity = shtc3.readHumidity();  // 讀取濕度

    if (isnan(temperature) || isnan(humidity)) {
        return false;  // 數據丟失，返回 false
    }

    return true;  // 成功讀取數據，返回 true
}