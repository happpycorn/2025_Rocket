constexpr const char* SSID = "ESP32_Receiver";
constexpr const char* PASSWORD = "00000000";

#include <WiFi.h>

#include "Constant.h"
#include "MonitorServer.h"

MonitorServer mserver;
RecordData data;
portMUX_TYPE dataMux = portMUX_INITIALIZER_UNLOCKED;

void fillTestRecordData() {
    data.time = 123456789ULL;
    data.slope_index -= 3;
    data.warning_index -= 2;
    data.slope_overflow = false;
    data.warning_overflow = false;

    // slope_data: [time, alt, vel, acc]
    data.slope_data[SLOPE_INDEX_MAX-3][0] = 0.0f;     data.slope_data[SLOPE_INDEX_MAX-3][1] = 10.0f;  data.slope_data[SLOPE_INDEX_MAX-3][2] = 1.0f;   data.slope_data[SLOPE_INDEX_MAX-3][3] = 0.1f;
    data.slope_data[SLOPE_INDEX_MAX-2][0] = 0.1f;     data.slope_data[SLOPE_INDEX_MAX-2][1] = 12.0f;  data.slope_data[SLOPE_INDEX_MAX-2][2] = 1.5f;   data.slope_data[SLOPE_INDEX_MAX-2][3] = 0.2f;
    data.slope_data[SLOPE_INDEX_MAX-1][0] = 0.2f;     data.slope_data[SLOPE_INDEX_MAX-1][1] = 15.0f;  data.slope_data[SLOPE_INDEX_MAX-1][2] = 2.0f;   data.slope_data[SLOPE_INDEX_MAX-1][3] = 0.3f;

    // attit_data: rol, pit, yaw
    data.attit_data[0] = 10.0f;
    data.attit_data[1] = -5.0f;
    data.attit_data[2] = 90.0f;

    // rocket_state: [Para1, Para2, Para3, Fail1, Fail2, Sensor1~Sensor7]
    for (int i = 0; i < BOOL_DATA_LEN; i++) {
        data.rocket_state[i] = (i % 2 == 0);  // true, false, true, ...
    }

    // gps_data_d: [rocket_lat, rocket_lon, self_lat, self_lon]
    data.gps_data_d[0] = 25.0478;   // rocket_lat
    data.gps_data_d[1] = 121.5319;  // rocket_lon
    data.gps_data_d[2] = 25.0330;   // self_lat
    data.gps_data_d[3] = 121.5654;  // self_lon

    // local_gps_data_f
    for (int i = 0; i < GPS_FLOAT_DATA_LEN; i++) {
        data.local_gps_data_f[i] = i * 1.1f;
    }

    data.max_alt = 100.0;

    data.last_recive_time = 123456799ULL;
    data.recive_pack_count = 42;

    data.warning[WARNING_INDEX_MAX-2] = "Altitude anomaly";
    data.warning[WARNING_INDEX_MAX-1] = "Parachute delay";
}


void setup() {
    Serial.begin(115200);

    WiFi.softAP(SSID, PASSWORD);
    Serial.println("AP Started. IP: ");
    Serial.println(WiFi.softAPIP());

    if (!mserver.begin()) {
        Serial.println("SPIFFS init failed!");
        while (1);
    }

    fillTestRecordData();
}

void loop() {
    mserver.handleClient();
}