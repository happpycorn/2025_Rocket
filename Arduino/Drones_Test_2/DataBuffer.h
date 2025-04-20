#pragma once

#include <Arduino.h>
#include "Constant.h"

class DataBuffer {
private:
    QueueHandle_t dataQueue; // 創建 Queue 變數

public:
    void createQueue();  // 創建 Queue 方法
    void saveData(const HFreqSensorData& data);
    bool getData(float f_data[], bool b_data[]);
};
