#include "0_Config.h"

ServoController servos[SERVO_COUNT] = {
    ServoController(SERVO_PIN_1),
    ServoController(SERVO_PIN_2),
    ServoController(SERVO_PIN_3)
};

BMPController bmps[BMP_COUNT] = {
    BMPController(BMP_I2C_ADDRESS_1, STANDARD_PRESSURE_1),
    BMPController(BMP_I2C_ADDRESS_2, STANDARD_PRESSURE_2)
};

Accelerometer accel;  // 創建 IMU 物件
Hygrometer hygro;  // 創建濕度計物件

DataBuffer dataBuffer; // 創建數據緩存器物件

ParachuteSystem parachuteSystem;  // 創建開傘系統物件

// 定義延遲時間
const TickType_t xFrequencyTask1 = pdMS_TO_TICKS(TASK_1_DELAY_MS);  // Task1: 10ms = 100Hz
const TickType_t xFrequencyTask2 = pdMS_TO_TICKS(TASK_2_DELAY_MS);  // Task2: 20ms = 50Hz

// 高頻 Task（100Hz）：感測器讀取、開傘判斷、伺服控制
void HighFreqTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount(); 

    while (1) {

        SensorData sensorData;
        SensorState sensor_state;

        // 氣壓計讀取
        float tempSum = 0, pressSum = 0, altSum = 0;
        int validCount = 0;
    
        // 取得所有數值
        for (int i = 0; i < BMP_COUNT; i++) {
            float t, p, a;
            sensor_state.barometer[i] = bmps[i].getData(t, p, a);
            if (sensor_state.barometer[i]) {
                tempSum += t;
                pressSum += p;
                altSum += a;
                validCount++;
            }
        }

        // 根據有效數值的數量計算實際數值
        if (validCount > 0) {
            // sensorData.temperature  = tempSum / validCount;
            sensorData.pressure = pressSum / validCount;
            sensorData.altitude = altSum / validCount;
        } else {
            // sensorData.temperature = 0;
            sensorData.pressure = 0;
            sensorData.altitude = 0;
        }

        // 濕度計讀取
        float t = 0;
        sensor_state.hygro = hygro.getData(t, sensorData.humidity);

        // 溫度特別處理
        if (sensor_state.hygro) {
            tempSum += t;
            validCount++;
        }

        // 根據有效數值的數量計算溫度
        if (validCount > 0) {
            sensorData.temperature = tempSum / validCount;
        } else {
            sensorData.temperature = 0;
        }

        // 加速度計讀取
        sensor_state.accel = accel.getData(
            sensorData.accels, 
            sensorData.gyros, 
            sensorData.mags, 
            sensorData.aSqrt, 
            sensorData.mDirection
        );

        // 儲存讀取狀態
        sensorData.sensor_state = sensor_state;

        // 判斷開傘
        bool s_sta[3];
        parachuteSystem.decideDeployment(
            sensorData.altitude, sensorData.slope,
            s_sta, sensorData.chute1Failed, sensorData.chute2Failed
        );

        // 如果狀態改變，設定伺服器角度
        for (int i = 0; i < 3; i++) {
            if (s_sta[i] != servos[i].isOpen) {
                servos[i].setServoAngle(s_sta[i]);
            }
        }

        // 儲存數據到 Queue
        dataBuffer.saveData(sensorData);

        // 保持 100Hz 更新
        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask1);
    }
}

// 低頻 Task（1Hz）：GPS 讀取、LoRa 傳輸、SD 卡存儲
void LowFreqTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        // 讀取 GPS
        Serial.println("低頻 Task：GPS 讀取 & LoRa 傳輸 & SD 卡存儲");
        
        // LoRa 傳輸
        // sendDataLoRa();
        
        // SD 卡存儲
        // saveDataToSD();

        // 保持 1Hz 更新
        vTaskDelayUntil(&xLastWakeTime, xFrequencyTask2);
    }
}

void setup() {
    Serial.begin(115200);
    Wire.begin();

    InitData init_record;
    
    for (int i = 0; i < SERVO_COUNT; i++) { servos[i].begin(); }
    
    for (int i = 0; i < BMP_COUNT; i++) { init_record.barometers[i] = bmps[i].begin(); }

    init_record.accel = accel.begin(&Wire);
    init_record.hygro = hygro.begin();

    dataBuffer.createQueue();

    xTaskCreatePinnedToCore(HighFreqTask, "HighFreqTask", 4096, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(LowFreqTask, "LowFreqTask", 4096, NULL, 1, NULL, 1);
}   

void loop() {}
