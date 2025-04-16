#pragma once

#define SDA_PIN 21
#define SCL_PIN 22

#define QUEUE_LENGTH 200

// 0~5 BMP*2, 6~8 Slope, 9~19 Acc, 20~21 Hgyro
#define HF_FLOAT_DATA_LEN 22
#define BMP_DATA_ADDR_1 0
#define BMP_DATA_ADDR_2 3
#define ACC_DATA_ADDR 9
#define HGYRP_DATA_ADDR 20

// 0~2 Servo, 3~4 Fail, 5~8 Sensor
#define HF_BOOL_DATA_LEN 9

typedef struct {
    float f[HF_FLOAT_DATA_LEN];
    bool b[HF_BOOL_DATA_LEN];
} HFreqSensorData;

// 0~21 HFData, 22~35 GPS
#define LF_FLOAT_DATA_LEN HF_FLOAT_DATA_LEN+14

// 0~8 HFData
#define LF_BOOL_DATA_LEN HF_BOOL_DATA_LEN

// 0~1 GPS
#define LF_DOUBLE_DATA_LEN 2

typedef struct {
    double d[LF_DOUBLE_DATA_LEN];
    float f[LF_FLOAT_DATA_LEN];
    bool b[LF_BOOL_DATA_LEN];
} LFreqData;