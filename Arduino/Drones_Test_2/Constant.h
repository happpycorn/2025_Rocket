#pragma once

// For Polymorphism
#define HFREQ_SENSOR_COUNT 4

// For BMP
#define BMP_I2C_ADDRESS_1 0x76
#define BMP_I2C_ADDRESS_2 0x77

// For Acc
#define SDA_PIN 21
#define SCL_PIN 22

// For GPS
#define GPS_UART_CHANNEL 1
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600
#define GPS_DATA_AGE_LIMIT 2000

// For SD_cards
#define SD_CS_PIN 5

// For LoRa
#define LORA_UART_CHANNEL 1
#define LORA_RX_PIN 14
#define LORA_TX_PIN 13
#define LORA_BAUD 9600

// For Quene
#define QUEUE_LENGTH 200

// 0~5 BMP*2, 6~8 Slope, 9~19 Acc, 20~21 Hgyro
#define HF_FLOAT_DATA_LEN 22
#define BMP_DATA_ADDR_1 0
#define BMP_DATA_ADDR_2 3
#define ACC_DATA_ADDR 9
#define HGYRP_DATA_ADDR 20
#define SLOPE_DATA_ADDR 6

// 0~2 Servo, 3~4 Fail, 5~8 Sensor
#define HF_BOOL_DATA_LEN 9
#define SERVO_DATA_ADDR 0
#define FAIL_DATA_ADDR 3
#define SENSOR_DATA_ADDR 5

typedef struct {
    float f[HF_FLOAT_DATA_LEN];
    bool b[HF_BOOL_DATA_LEN];
} HFreqSensorData;

// 0~21 HFData, 22~32 GPS
#define LF_FLOAT_DATA_LEN HF_FLOAT_DATA_LEN+11
#define GPS_DATA_ADDR HF_FLOAT_DATA_LEN

// 0~8 HFData, 9 isHFData, 10 GPS
#define LF_BOOL_DATA_LEN HF_BOOL_DATA_LEN+2
#define IS_HFD_ADDR HF_BOOL_DATA_LEN+0
#define IS_GPS_ADDR HF_BOOL_DATA_LEN+1

// 0~1 GPS
#define LF_DOUBLE_DATA_LEN 2

#pragma pack(1)
typedef struct {
    float f[LF_FLOAT_DATA_LEN];
    bool b[LF_BOOL_DATA_LEN];
    double d[LF_DOUBLE_DATA_LEN];
} LFreqData;

// For Task
#define TASK_1_DELAY_MS 10
#define TASK_2_DELAY_MS 1000

// For PRC System
#define PRC_BUFFER_SIZE 100