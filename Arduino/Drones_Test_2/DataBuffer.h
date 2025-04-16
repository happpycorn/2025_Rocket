#pragma once

#include <Arduino.h>
#include "Constant.h"

class DataBuffer {
private:
    QueueHandle_t dataQueue; // 創建 Queue 變數
    int queueLength = QUEUE_LENGTH;

public:
    void createQueue();  // 創建 Queue 方法
    void saveData(SensorData data);
    bool getData(TotalData& data);

};
