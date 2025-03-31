#ifndef DATABUFFER_H
#define DATABUFFER_H

// #include <Arduino.h>
// #include <FreeRTOS.h>
#include <queue.h>   // 引入隊列相關函數
#include <0_Config.h>

class DataBuffer {
private:

    QueueHandle_t dataQueue; // 創建 Queue 變數
    int queueLength;

public:
    // 建構子
    DataBuffer(int length = 200);

    // 儲存數據方法
    void saveData(SensorData data);
    bool getData(TotalData &data);
    void createQueue();  // 創建 Queue 方法

};

#endif // DATABUFFER_H
