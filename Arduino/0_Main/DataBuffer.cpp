#include <DataBuffer.h>

DataBuffer::DataBuffer(int length) : queueLength(length) {}

void DataBuffer::saveData(SensorData data) {
    xQueueSend(dataQueue, &data, 0); // 傳入 Queue
}

bool DataBuffer::getData(TotalData &data) {

    if (uxQueueMessagesWaiting(dataQueue) == 0) {

        data.temperature = 0.0;
        data.press = 0.0;
        data.alt = 0.0;
        data.humidity = 0.0;

        for (int i = 0; i < 3; i++) {
            data.accels[i] = 0.0;
            data.gyros[i] = 0.0;
            data.mags[i] = 0.0;
        }

        for (int i = 0; i < 3; i++) {
            data.servos_state[i] = false;
        }

        return false;
    }

    SensorData dataBuffer[200];
    int count = 0;

    while (count < 200 && uxQueueReceive(dataQueue, &dataBuffer[count], portMAX_DELAY) == pdPASS) {
        count++;
    }

    float sum_temp = 0;
    float sum_press = 0;
    float sum_altitude = 0;
    float sum_humidity = 0;

    float sum_accels[3] = {0.0, 0.0, 0.0};
    float sum_gyros[3] = {0.0, 0.0, 0.0};
    float sum_mags[3] = {0.0, 0.0, 0.0};

    for (int i = 0; i < 3; i++) {
        data.servos_state[i] = false;
    }

    for (int i = 0; i < count; i++) {

        sum_temp += dataBuffer[i].temperature;
        sum_press += dataBuffer[i].pressure;
        sum_altitude += dataBuffer[i].altitude;
        sum_humidity += dataBuffer[i].humidity;

        for (int j = 0; j < 3; j++) {
            sum_accels[i] += dataBuffer[i].accels[j];
            sum_gyros[i] += dataBuffer[i].gyros[j];
            sum_mags[i] += dataBuffer[i].mags[j];
        }

        for (int j = 0; j < 3; j++) {
            if (dataBuffer[i].servos_state[j]) servos_state[j] = true;
        }
    }

    data.temperature = sum_temp / count;
    data.pressure = sum_press / count;
    data.altitude = sum_altitude / count;
    data.humidity = sum_humidity / count;

    for (int i = 0; i < 3; i++){
        data.accels[i] = sum_accels[i] / count;
        data.gyros[i] = sum_gyros[i] / count;
        data.mags[i] = sum_mags[i] / count;
    }
    
    return true;
}

void DataBuffer::createQueue() {
    dataQueue = xQueueCreate(queueLength, sizeof(SensorData));
}
