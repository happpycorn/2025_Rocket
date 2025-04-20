#include "Config.h"

HFreqSensor* hfSensor[HFREQ_SENSOR_COUNT] = {
    new BMPController(BMP_I2C_ADDRESS_1, STANDARD_PRESSURE_1, BMP_DATA_ADDR_1),
    new BMPController(BMP_I2C_ADDRESS_2, STANDARD_PRESSURE_2, BMP_DATA_ADDR_2),
    new Accelerometer(ACC_DATA_ADDR),
    new Hygrometer(HGYRP_DATA_ADDR)
};

SDDataManager sd;
DataBuffer buffer;
GPSModule gps(GPS_DATA_ADDR);

const TickType_t xFrequencyTask1 = pdMS_TO_TICKS(TASK_1_DELAY_MS);
const TickType_t xFrequencyTask2 = pdMS_TO_TICKS(TASK_2_DELAY_MS);

void HighFreqTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount(); 

    while (1) {
        HFreqSensorData data;

        // 讀取數據
        for (int i = 0; i < HFREQ_SENSOR_COUNT; i++) {
            data.b[SENSOR_DATA_ADDR+i] = hfSensor[i]->getData(data.f);
        }

        // 計算平均高度與斜率
        data.f[SLOPE_DATA_ADDR+0] = calculateAveAlt(
            data.b[SENSOR_DATA_ADDR+0], data.b[SENSOR_DATA_ADDR+1],
            data.f[BMP_DATA_ADDR_1+2], data.f[BMP_DATA_ADDR_2+2]
        );

        unsigned long long now = millis();
        prcSystem.calculateSlope(now, data.f[SLOPE_DATA_ADDR+0], data.f);

        // 決定開傘
        bool isLaunch;
        prcSystem.decideDeployment(
            data.f[SLOPE_DATA_ADDR+0], data.f[SLOPE_DATA_ADDR+0], isLaunch
        );

        myServo.setServoAngle(isLaunch);

        // 儲存資料
        buffer.saveData(data);

        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask1);
    }
}

void LowFreqTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        LFreqData data;

        // 讀取資料
        data.isHaveSensor = dataBuffer.getData(data);
        gps.getData(data.d, data.f);
        
        // LoRa 傳輸
        loRaDataSender.sendTotalData(data);
        
        // SD 卡存儲
        sd.saveData(data);

        // 保持 1Hz 更新
        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask2);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Init...");

    bool is_hfs_init = true;
    for (int i = 0; i < HFREQ_SENSOR_COUNT; i++) {
        bool ok = hfSensor[i]->begin();
        Serial.print(i); Serial.print(": ");
        Serial.println(ok ? "true" : "false");
        is_hfs_init &= ok;
    }
    if (!is_hfs_init) {
        Serial.println("High Frequence Sensor Init Fail.");
        while (1);
    }

    if (!sd.begin()) {
        Serial.println("SD Card Init Fail.");
        while (1);
    }
    
    // Fill Slope Data
    Serial.println("Filling Slope Data...");
    int fillCount = PRC_BUFFER_SIZE*2;
    float data[6];
    float alt;
    unsigned long long now;
    for (int i = 0; i < fillCount; i++) {
        now = millis();
        bool b1 = hfSensor[0].getData(data);
        bool b2 = hfSensor[1].getData(data);
        alt = calculateAveAlt(b1, b2, data[2], data[5]);
        prcSystem.fillSpace(now, alt);
    }

    Serial.println("Start!");
}

void loop() {}