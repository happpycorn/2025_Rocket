#pragma once

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
#define HEADER1 0xAA
#define HEADER2 0x55
#define BINARY_LENGTH 35
#define LORA_BUFFER_LEN 64

// For Quene
#define QUEUE_LENGTH 200

// 0~21 HFData, 22~32 GPS
#define LF_FLOAT_DATA_LEN 11
#define GPS_DATA_ADDR 0

// 0~8 HFData, 9 isHFData, 10 GPS
#define LF_BOOL_DATA_LEN 1
#define IS_GPS_ADDR 0

// 0~1 GPS
#define LF_DOUBLE_DATA_LEN 2

typedef struct {
    float f[LF_FLOAT_DATA_LEN];
    bool b[LF_BOOL_DATA_LEN];
    double d[LF_DOUBLE_DATA_LEN];
} LFreqData;

#define RECIVE_FLOAT_DATA_LEN 3
#define RECIVE_BOOL_DATA_LEN 11
#define RECIVE_DOUBLE_DATA_LEN 2