#ifndef CONFIG_H
#define CONFIG_H

#include <SD.h>
#include <SPI.h>

// For Barometer
#define BMP390_I2C_ADDRESS_1 0x76
#define BMP390_I2C_ADDRESS_2 0x77
#define STANDARD_PRESSURE_1 1007.05
#define STANDARD_PRESSURE_2 1007.36

// For Accelerometer
#define SDA_PIN 21
#define SCL_PIN 22

// For Servo
#define SERVO_PIN 32

// For SD
#define SD_CS 5

// For PRC System
#define BUFFER_SIZE 100
#define LAUNCH_UPPER_BOUND 50
#define LAUNCH_BELOW_BOUND 30
#define LAUNCH_SLOPE -0.3

#include "Barometer.h"
#include "ParachuteSystem.h"
#include "ServoController.h"
#include "Accelerometer.h"
#include "Hygrometer.h"

#endif // CONFIG_H