#include "SDDataManager.h"

SDDataManager sdManager;

TotalData generateTestData();

void setup() {
    Serial.begin(115200);

    if (!sdManager.begin()) {
        Serial.println("初始化 SD 卡失敗!");
        while (1);
    }
    Serial.println("SD 卡初始化成功!");

    TotalData totaldata = generateTestData();

    if (sdManager.saveData(totaldata)) {
        Serial.println("SD 卡寫入成功!");
    } else {
        Serial.println("SD 卡寫入失敗!");
    }
}

void loop() {
  // 這裡不需要任何操作，因為不需要讀取數據
}

// **靜態測試數據**
TotalData generateTestData() {
    TotalData data;

    data.temperature = 25.0;        // 溫度 25°C
    data.pressure = 1013.25;        // 氣壓 1013.25 hPa
    data.altitude = 500.0;          // 高度 500 米
    data.humidity = 50.0;           // 濕度 50%

    data.accels[0] = 0.0;           // 加速度 x 軸
    data.accels[1] = 0.0;           // 加速度 y 軸
    data.accels[2] = 0.0;           // 加速度 z 軸

    data.gyros[0] = 0.0;           // 角速度 x 軸
    data.gyros[1] = 0.0;           // 角速度 y 軸
    data.gyros[2] = 0.0;           // 角速度 z 軸

    data.mags[0] = 0.0;            // 磁場 x 軸
    data.mags[1] = 0.0;            // 磁場 y 軸
    data.mags[2] = 0.0;            // 磁場 z 軸

    data.aSqrt = 0.0;              // 加速度的平方和
    data.mDirection = 0.0;         // 磁場方向
    data.slope = 0.0;              // 坡度

    // 伺服狀態
    data.servos_state[0] = false;
    data.servos_state[1] = false;
    data.servos_state[2] = false;

    data.chute1Failed = false;     // 第一個降落傘故障
    data.chute2Failed = false;     // 第二個降落傘故障

    data.sensor_state.barometer[0] = true;
    data.sensor_state.barometer[1] = true;
    data.sensor_state.accel = true;
    data.sensor_state.hygro = true;

    data.isHaveSensor = true;

    // GPS 數據
    data.gps_data.latitude = 37.7749;         // 緯度 (37.7749°)
    data.gps_data.longitude = -122.4194;      // 經度 (-122.4194°)
    data.gps_data.altitude = 50.0;            // 海拔 50 米
    data.gps_data.geoidSeparation = 0.0;      // 大地水準面高度
    data.gps_data.utcTime = 1609459200000;    // UTC 時間 (2021年1月1日的毫秒級時間)
    data.gps_data.groundSpeed = 20.0;         // 地面速度 20 m/s
    data.gps_data.heading = 90.0;             // 航向角 90°
    data.gps_data.verticalSpeed = 0.0;        // 垂直速度 0 m/s
    data.gps_data.numSatellites = 10;         // 連接衛星數量
    data.gps_data.numVisibleSat = 12;         // 可見衛星數量
    data.gps_data.hdop = 1.0;                 // 水平精度指標 (HDOP)
    data.gps_data.pdop = 1.5;                 // 3D精度指標 (PDOP)
    data.gps_data.signalQuality = 40;         // 訊號強度
    data.gps_data.fixType = 3;                // GPS Fix 類型 (3D Fix)
    data.gps_data.gnssSystem = 0;             // GPS 系統
    data.gps_data.accEst = 2.0;               // 位置精度估計 (m)
    data.gps_data.accVel = 0.1;               // 速度精度估計 (m/s)

    return data;
}
