#include <DataBuffer.h>

void DataBuffer::saveData(const HFreqSensorData& data) {
    xQueueSend(dataQueue, &data, portMAX_DELAY); // 傳入 Queue
}

bool DataBuffer::getData(float f_data[], bool b_data[]) {

    if (uxQueueMessagesWaiting(dataQueue) == 0) {
        for (int i = 0; i < HF_FLOAT_DATA_LEN; i++) { f_data[i] = 0.0; }
        for (int i = 0; i < HF_BOOL_DATA_LEN; i++) { b_data[i] = 0.0; }

        return false;
    }

    HFreqSensorData dataBuffer[QUEUE_LENGTH];
    int count = 0;

    while (count < QUEUE_LENGTH && xQueueReceive(dataQueue, &dataBuffer[count], portMAX_DELAY) == pdPASS) {
        count++;
    }

    // 初始化累加器
    float sum[HF_FLOAT_DATA_LEN] = {0};
    bool result_b[HF_BOOL_DATA_LEN];
    for (int i = 0; i < HF_BOOL_DATA_LEN; i++) {
        result_b[i] = true; // 預設為 true，遇到 false 就變 false
    }

    // 累加所有資料
    for (int i = 0; i < count; i++) {
        for (int j = 0; j < HF_FLOAT_DATA_LEN; j++) {
            sum[j] += dataBuffer[i].f[j];
        }
        for (int j = 0; j < HF_BOOL_DATA_LEN; j++) {
            result_b[j] &= dataBuffer[i].b[j];
        }
    }

    // 計算平均
    for (int i = 0; i < HF_FLOAT_DATA_LEN; i++) {
        f_data[i] = sum[i] / count;
    }

    // 複製 bool 結果
    for (int i = 0; i < HF_BOOL_DATA_LEN; i++) {
        b_data[i] = result_b[i];
    }

    return true;
}

void DataBuffer::createQueue() {
    dataQueue = xQueueCreate(queueLength, sizeof(HFreqSensorData));
}
