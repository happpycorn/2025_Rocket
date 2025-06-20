#include "Config.h"

LoRaDataReciver lora;
GPSModule gps(0);
RecordData data;
SDDataManager sd;
MonitorServer mserver;

portMUX_TYPE dataMux = portMUX_INITIALIZER_UNLOCKED;

const TickType_t xFrequencyTask2 = pdMS_TO_TICKS(TASK_2_DELAY_MS);

void LowFreqTask(void *pvParameters) {
    TickType_t xLastWakeTime = xTaskGetTickCount();
    
    while (1) {
        portENTER_CRITICAL(&dataMux);
        data.time = millis();

        // GPS
        double g_d[GPS_DOUBLE_DATA_LEN];
        data.rocket_state[LOCAL_GPS_BOOL_ADDR] = gps.getData(g_d, data.local_gps_data_f);
        for (int i = LOCAL_GPS_DOUBLE_ADDR; i < DOUBLE_DATA_LEN; i++) data.gps_data_d[i] = g_d[i-LOCAL_GPS_DOUBLE_ADDR];
        RecordData current;                    // 宣告一份副本
        current = data;                        // 將共享變數 data 複製到副本
        portEXIT_CRITICAL(&dataMux);

        // SD
        sd.saveData(current);
    }
}

void setup() {
    Serial.begin(115200);       // 給電腦看的 Serial
    lora.begin();
    gps.begin();

    if (!sd.begin()) {
        Serial.println("SD Card Init Fail.");
        while (1);
    }

    if (!mserver.begin()) {
        Serial.println("SPIFFS init failed!");
        while (1);
    }

    // 啟用 WiFi AP 模式
    WiFi.softAP(SSID, PASSWORD);
    Serial.println("AP Started. IP: ");
    Serial.println(WiFi.softAPIP());

    xTaskCreatePinnedToCore(LowFreqTask, "LowFreqTask", 12288, NULL, 1, NULL, 1);
}

void loop() {
   Result r = lora.reciveData();
    if (r.message != nullptr) Serial.println(r.message);
    if (r.data.is_data) {
        portENTER_CRITICAL(&dataMux);
        data.last_recive_time = millis();
        data.recive_pack_count = r.data.pack_count;
        data.slope_data[data.slope_index][0] = data.last_recive_time;
        for (int i = 1; i < 4; i++) data.slope_data[data.slope_index][i] = r.data.f[i-1];
        for (int i = 3; i < RECIVE_FLOAT_DATA_LEN; i++) data.attit_data[i] = r.data.f[i];
        for (int i = 0; i < RECIVE_BOOL_DATA_LEN; i++) data.rocket_state[i] = r.data.b[i];
        for (int i = 0; i < RECIVE_DOUBLE_DATA_LEN; i++) data.gps_data_d[i] = r.data.d[i];
        data.slope_index = (data.slope_index + 1)%SLOPE_INDEX_MAX;
        portEXIT_CRITICAL(&dataMux);
    }

    mserver.handleClient();
}
