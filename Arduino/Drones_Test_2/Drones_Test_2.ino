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
LoRaDataSender lora;
ServoController myServo(SERVO_PIN);
ParachuteSystem prc;

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
        data.f[SLOPE_DATA_ADDR+0] = prc.calculateAveAlt(
            data.b[SENSOR_DATA_ADDR+0], data.b[SENSOR_DATA_ADDR+1],
            data.f[BMP_DATA_ADDR_1+2], data.f[BMP_DATA_ADDR_2+2]
        );

        unsigned long long now = millis();
        prc.calculateSlope(now, data.f[SLOPE_DATA_ADDR+0], data.f);

        // 決定開傘
        bool isLaunch;
        prc.decideDeployment(
            data.f[SLOPE_DATA_ADDR+0], data.f[SLOPE_DATA_ADDR+1], isLaunch
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

        data.b[IS_HFD_ADDR] = buffer.getData(data.f, data.b);
        data.b[IS_GPS_ADDR] = gps.getData(data.d, data.f);

        lora.sendData(data.f, data.b, data.d);

        sd.saveData(data);

        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask2);
    }
}

void setup() {
    Serial.begin(115200);
    Serial.println("Init...");

    if (!lora.begin()) {
        Serial.println("LoRa Init Fail.");
        while (1);
    }

    bool is_hfs_init = true;
    for (int i = 0; i < HFREQ_SENSOR_COUNT; i++) {
        bool ok = hfSensor[i]->begin();
        Serial.print(i); Serial.print(": ");
        Serial.println(ok ? "true" : "false");
        is_hfs_init &= ok;
    }
    if (!is_hfs_init) {
        lora.println("High Frequence Sensor Init Fail.");
        Serial.println("High Frequence Sensor Init Fail.");
        while (1);
    }

    if (!sd.begin()) {
        lora.println("SD Card Init Fail.");
        Serial.println("SD Card Init Fail.");
        while (1);
    }
    
    // Fill Slope Data
    lora.println("Filling Slope Data...");
    Serial.println("Filling Slope Data...");
    int fillCount = PRC_BUFFER_SIZE*2;
    float data[6];
    float alt;
    unsigned long long now;
    for (int i = 0; i < fillCount; i++) {
        now = millis();
        bool b1 = hfSensor[0]->getData(data);
        bool b2 = hfSensor[1]->getData(data);
        alt = prc.calculateAveAlt(b1, b2, data[2], data[5]);
        prc.fillSpace(now, alt);
    }

    lora.println("Start!");
    Serial.println("Start!");

    xTaskCreatePinnedToCore(HighFreqTask, "HighFreqTask", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(LowFreqTask, "LowFreqTask", 4096, NULL, 1, NULL, 1);
}

void loop() {}