#pragma once

#include <Arduino.h>

// For Polymorphism
constexpr int HFREQ_SENSOR_COUNT = 4;

// For BMP
constexpr uint8_t BMP_I2C_ADDRESS_1 = 0x76;
constexpr uint8_t BMP_I2C_ADDRESS_2 = 0x77;

// For Acc
constexpr int SDA_PIN = 21;
constexpr int SCL_PIN = 22;

// For GPS
constexpr int GPS_UART_CHANNEL = 1;
constexpr int GPS_RX_PIN = 16;
constexpr int GPS_TX_PIN = 17;
constexpr int GPS_BAUD = 9600;
constexpr int GPS_DATA_AGE_LIMIT = 2000;
constexpr int GPS_FLOAT_DATA_LEN = 11;
constexpr int GPS_DOUBLE_DATA_LEN = 2;

// For SD_cards
constexpr int SD_CS_PIN = 5;

// For LoRa
constexpr int LORA_UART_CHANNEL = 2;
constexpr int LORA_RX_PIN = 13;
constexpr int LORA_TX_PIN = 14;
constexpr int LORA_BAUD = 9600;
constexpr uint8_t HEADER1 = 0xAA;
constexpr uint8_t HEADER2 = 0x55;
constexpr uint8_t TYPE_DATA = 0x01;
constexpr uint8_t TYPE_TEXT = 0x02;
constexpr int BINARY_LENGTH = 46;
constexpr int LORA_BUFFER_LEN = 64;

// For Servo
constexpr int SERVO_PIN_1 = 26;
constexpr int SERVO_PIN_2 = 25;
constexpr int SERVO_PIN_3 = 33;

// For Quene
constexpr int QUEUE_LENGTH = 200;

// 0~5 BMP*2, 6~8 Slope, 9~20 Acc, 21~22 Hgyro
constexpr int HF_FLOAT_DATA_LEN = 23;
constexpr int BMP_DATA_ADDR_1 = 0;
constexpr int BMP_DATA_ADDR_2 = 3;
constexpr int SLOPE_DATA_ADDR = 6;
constexpr int ACC_DATA_ADDR = 9;
constexpr int HGYRP_DATA_ADDR = 21;

// 0~2 Servo, 3~4 Fail, 5~8 Sensor
constexpr int HF_BOOL_DATA_LEN = 9;
constexpr int SERVO_DATA_ADDR = 0;
constexpr int FAIL_DATA_ADDR = 3;
constexpr int SENSOR_DATA_ADDR = 5;

typedef struct {
    float f[HF_FLOAT_DATA_LEN];
    bool b[HF_BOOL_DATA_LEN];
} HFreqSensorData;

// 0~21 HFData, 22~32 GPS
constexpr int LF_FLOAT_DATA_LEN = HF_FLOAT_DATA_LEN+11;
constexpr int GPS_DATA_ADDR = HF_FLOAT_DATA_LEN;

// 0~8 HFData, 9 isHFData, 10 GPS
constexpr int LF_BOOL_DATA_LEN = HF_BOOL_DATA_LEN+2;
constexpr int IS_HFD_ADDR = HF_BOOL_DATA_LEN+0;
constexpr int IS_GPS_ADDR = HF_BOOL_DATA_LEN+1;

// 0~1 GPS
constexpr int LF_DOUBLE_DATA_LEN = 2;

typedef struct {
    float f[LF_FLOAT_DATA_LEN];
    bool b[LF_BOOL_DATA_LEN];
    double d[LF_DOUBLE_DATA_LEN];
} LFreqData;

// For Task
constexpr int TASK_1_DELAY_MS = 10;
constexpr int TASK_2_DELAY_MS = 1000;

// For PRC System
constexpr int PRC_BUFFER_SIZE = 100;
constexpr int LAUNCH_SLOPE = -0.3;
constexpr int UNFAIL_SUB_SLOPE = 1;
constexpr int LAUNCH_BELOW_BOUND = 100;
constexpr int DEPLOY_DELAY = 5000;

// For Servo
constexpr int SERVO_COUNT = 3;

// For Recive Data
constexpr int RECIVE_FLOAT_DATA_LEN = 6;
constexpr int RECIVE_BOOL_DATA_LEN = 11;
constexpr int RECIVE_DOUBLE_DATA_LEN = 2;

// For Local Data
constexpr int FLOAT_DATA_LEN = RECIVE_FLOAT_DATA_LEN+11;
constexpr int LOCAL_GPS_FLOAT_ADDR = RECIVE_FLOAT_DATA_LEN;
constexpr int BOOL_DATA_LEN = RECIVE_BOOL_DATA_LEN+1;
constexpr int LOCAL_GPS_BOOL_ADDR = RECIVE_BOOL_DATA_LEN;
constexpr int DOUBLE_DATA_LEN = RECIVE_DOUBLE_DATA_LEN+2;
constexpr int LOCAL_GPS_DOUBLE_ADDR = RECIVE_DOUBLE_DATA_LEN;

// For Record Data
constexpr int SLOPE_INDEX_MAX = 300;
constexpr int WARNING_INDEX_MAX = 100;

typedef struct {
    // Sys
    unsigned long long time;
    int slope_index = SLOPE_INDEX_MAX;
    int warning_index = WARNING_INDEX_MAX;
    bool slope_overflow = false;
    bool warning_overflow = false;

    // Data
    float slope_data[SLOPE_INDEX_MAX][4];   // time, alt, vel, acc
    float attit_data[3];        // rol, pit, yaw
    bool rocket_state[BOOL_DATA_LEN];       // 0~2 Para, 3~4 Fail, 5~11 Sensor
    double gps_data_d[DOUBLE_DATA_LEN];       // 0~1 rocket, 2~3 self
    float local_gps_data_f[GPS_FLOAT_DATA_LEN];
    float max_alt = -1.0 / 0.0;

    // LoRa
    unsigned long long last_recive_time;
    unsigned int recive_pack_count;

    // Warning
    String warning[WARNING_INDEX_MAX];

} RecordData;

typedef struct {
    int pack_count;
    float f[RECIVE_FLOAT_DATA_LEN];
    bool b[RECIVE_BOOL_DATA_LEN];
    double d[RECIVE_DOUBLE_DATA_LEN];
    bool is_data = false;
} ReciveData;

typedef struct {
    char message[LORA_BUFFER_LEN];
    bool is_message = false;
    ReciveData data;
} Result;

class HFreqSensor {
public:
    HFreqSensor(int addr) : data_addr(addr) {}
    virtual bool begin() = 0;
    virtual bool getData(float data[]) = 0;

protected:
    int data_addr;
};
