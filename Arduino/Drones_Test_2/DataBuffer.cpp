#include <DataBuffer.h>

void DataBuffer::saveData(HFreqSensorData data) {
    xQueueSend(dataQueue, &data, portMAX_DELAY); // 傳入 Queue
}

bool DataBuffer::getData(TotalData& data) {

    if (uxQueueMessagesWaiting(dataQueue) == 0) {

        data.temperature = 0.0;
        data.pressure = 0.0;
        data.altitude = 0.0;
        data.humidity = 0.0;
        for (int i = 0; i < 3; i++) {
            data.accels[i] = 0.0;
            data.gyros[i] = 0.0;
            data.mags[i] = 0.0;
        }
        data.aSqrt = 0.0;
        data.mDirection = 0.0;
        data.slope = 0.0;
        for (int i = 0; i < 3; i++) {
            data.servos_state[i] = false;
        }
        data.chute1Failed = false;
        data.chute2Failed = false;

        // 初始化 sensor_state
        data.sensor_state.barometer[0] = true;
        data.sensor_state.barometer[1] = true;
        data.sensor_state.accel = true;
        data.sensor_state.hygro = true;

        return false;
    }

    SensorData dataBuffer[200];
    int count = 0;

    while (count < 200 && xQueueReceive(dataQueue, &dataBuffer[count], portMAX_DELAY) == pdPASS) {
        count++;
    }

    float sum_temp = 0.0;
    float sum_press = 0.0;
    float sum_altitude = 0.0;
    float sum_humidity = 0.0;
    
    float sum_accels[3] = {0.0, 0.0, 0.0};
    float sum_gyros[3] = {0.0, 0.0, 0.0};
    float sum_mags[3] = {0.0, 0.0, 0.0};
    
    float sum_aSqrt = 0.0;
    float sum_mDirection = 0.0;
    float sum_slope = 0.0;
    
    // 初始化 servos_state 和 chute 相關的值
    bool servos_state[3] = {false, false, false};
    bool chute1Failed = false;
    bool chute2Failed = false;
    
    // 初始化 sensor_state
    SensorState sensor_state = { {true, true}, true, true };

    for (int i = 0; i < count; i++) {
        sum_temp += dataBuffer[i].temperature;
        sum_press += dataBuffer[i].pressure;
        sum_altitude += dataBuffer[i].altitude;
        sum_humidity += dataBuffer[i].humidity;
    
        for (int j = 0; j < 3; j++) {
            sum_accels[j] += dataBuffer[i].accels[j];
            sum_gyros[j] += dataBuffer[i].gyros[j];
            sum_mags[j] += dataBuffer[i].mags[j];
        }
    
        sum_aSqrt += dataBuffer[i].aSqrt;
        sum_mDirection += dataBuffer[i].mDirection;
        sum_slope += dataBuffer[i].slope;
    
        // 更新 servos_state 和 chute 失敗狀態
        for (int j = 0; j < 3; j++) {
            servos_state[j] |= dataBuffer[i].servos_state[j];  // 如果為 true，則保留 true
        }
    
        chute1Failed |= dataBuffer[i].chute1Failed;
        chute2Failed |= dataBuffer[i].chute2Failed;
    
        // 更新 sensor_state 的狀態
        sensor_state.barometer[0] &= dataBuffer[i].sensor_state.barometer[0];
        sensor_state.barometer[1] &= dataBuffer[i].sensor_state.barometer[1];
        sensor_state.accel &= dataBuffer[i].sensor_state.accel;
        sensor_state.hygro &= dataBuffer[i].sensor_state.hygro;
    }
    
    // 計算平均值並賦值給 data
    data.temperature = sum_temp / count;
    data.pressure = sum_press / count;
    data.altitude = sum_altitude / count;
    data.humidity = sum_humidity / count;
    
    for (int i = 0; i < 3; i++) {
        data.accels[i] = sum_accels[i] / count;
        data.gyros[i] = sum_gyros[i] / count;
        data.mags[i] = sum_mags[i] / count;
    }
    
    data.aSqrt = sum_aSqrt / count;
    data.mDirection = sum_mDirection / count;
    data.slope = sum_slope / count;
    
    // 更新 servos_state、chute 失敗狀態和 sensor_state
    for (int i = 0; i < 3; i++) {
        data.servos_state[i] = servos_state[i];
    }
    
    data.chute1Failed = chute1Failed;
    data.chute2Failed = chute2Failed;
    
    data.sensor_state = sensor_state;
    return true;
}

void DataBuffer::createQueue() {
    dataQueue = xQueueCreate(queueLength, sizeof(HFreqSensorData));
}
