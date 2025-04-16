#pragma once

// For Acc
#define SDA_PIN 21
#define SCL_PIN 22

// For GPS
#define GPS_UART_CHANNEL 1
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600
#define GPS_DATA_AGE_LIMIT 2000

// For Quene
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