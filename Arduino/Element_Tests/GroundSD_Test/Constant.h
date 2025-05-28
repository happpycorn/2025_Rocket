#pragma once

#include <WiFi.h>
#include <SPIFFS.h>
#include <WebServer.h>
#include <ArduinoJson.h>

// For GPS
#define GPS_UART_CHANNEL 1
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600
#define GPS_DATA_AGE_LIMIT 2000
#define GPS_FLOAT_DATA_LEN 11
#define GPS_DOUBLE_DATA_LEN 2

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

// For Recive Data
#define RECIVE_FLOAT_DATA_LEN 3
#define RECIVE_BOOL_DATA_LEN 11
#define RECIVE_DOUBLE_DATA_LEN 2

// For Local Data
#define FLOAT_DATA_LEN RECIVE_FLOAT_DATA_LEN+11
#define LOCAL_GPS_FLOAT_ADDR RECIVE_FLOAT_DATA_LEN
#define BOOL_DATA_LEN RECIVE_BOOL_DATA_LEN+1
#define LOCAL_GPS_BOOL_ADDR RECIVE_BOOL_DATA_LEN
#define DOUBLE_DATA_LEN RECIVE_DOUBLE_DATA_LEN+2
#define LOCAL_GPS_DOUBLE_ADDR RECIVE_DOUBLE_DATA_LEN

typedef struct {
    unsigned long long time;
    unsigned long long last_recive_time;
    unsigned int recive_pack_count;
    float f[FLOAT_DATA_LEN];
    bool b[BOOL_DATA_LEN];
    double d[DOUBLE_DATA_LEN];
} RecordData;

