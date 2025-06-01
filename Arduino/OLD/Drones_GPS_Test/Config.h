#ifndef CONFIG_H
#define CONFIG_H

#include <SD.h>
#include <SPI.h>

// For SD
#define SD_CS 5

// For GPS
#define GPS_RX_PIN 16
#define GPS_TX_PIN 17
#define GPS_BAUD 9600

#include "GPSModule.h"

#endif // CONFIG_H