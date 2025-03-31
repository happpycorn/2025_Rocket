#ifndef CONFIG_H
#define CONFIG_H

// 引入必要的庫
#include "ServoController.h"
#include "Accelerometer.h"
#include "Barometer.h"
#include "Hygrometer.h"
#include "ParachuteSystem.h"

// 定義延遲時間
#define TASK_1_DELAY_MS 10
#define TASK_2_DELAY_MS 1000

// 標準氣壓 (海平面壓力)
#define STANDARD_PRESSURE_1 1013.25
#define STANDARD_PRESSURE_2 1013.25

// 氣壓計 I2C 地址
#define BMP_COUNT 2
#define BMP_I2C_ADDRESS_1 0x76 
#define BMP_I2C_ADDRESS_2 0x77 

// 伺服馬達腳位設置
#define SERVO_COUNT 3
#define SERVO_PIN_1 26
#define SERVO_PIN_2 25
#define SERVO_PIN_3 33

struct SensorState {
    bool barometer[2];
    bool accel;
    bool hygro;
};

struct GPSData {
    // 位置資訊
    double latitude;      // 緯度 (°)
    double longitude;     // 經度 (°)
    float altitude;       // 高度（相對海平面, m）
    float geoidSeparation; // 大地水準面高度 (m)

    // 時間資訊
    uint32_t utcTime;     // UTC 時間（毫秒級）
    
    // 速度與運動方向
    float groundSpeed;    // 地面速度 (m/s)
    float heading;        // 航向角 (°)
    float verticalSpeed;  // 垂直速度 (m/s)

    // 衛星訊號品質
    uint8_t numSatellites; // 已連接衛星數
    uint8_t numVisibleSat; // 可見衛星數
    float hdop;           // 水平精度指標 (HDOP)
    float pdop;           // 3D 位置精度指標 (PDOP)
    uint8_t signalQuality;// 訊號強度指標 (SNR)

    // GNSS 相關資訊
    uint8_t fixType;      // GPS Fix 狀態（0=無, 1=2D, 2=3D, 3=DGPS）
    uint8_t gnssSystem;   // GNSS 系統標識（GPS/GLONASS/BeiDou）

    // 擴展資訊（UBX 解析）
    float accEst;         // 位置精度估計（m）
    float accVel;         // 速度精度估計（m/s）
};

struct SensorData {
    float temperature;
    float pressure;
    float altitude;
    float humidity;
    float accels[3];
    float gyros[3];
    float mags[3];
    float aSqrt;
    float mDirection;
    float slope;
    bool servos_state[3]; 
    bool chute1Failed;
    bool chute2Failed;
    SensorState sensor_state;
};

struct TotalData : public SensorData {
    GPSData gps;
};

struct InitData {
    bool barometers[2];
    bool accel;
    bool hygro;
    bool gps;
    bool lora;
    bool sdcard;
};

#include "DataBuffer.h"

#endif  // CONFIG_H
