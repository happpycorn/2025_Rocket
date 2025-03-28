#ifndef CONFIG_H
#define CONFIG_H

// 引入必要的庫
#include "Accelerometer.h"
#include "ServoController.h"
#include "Barometer.h"

// 標準氣壓 (海平面壓力)
#define STANDARD_PRESSURE 1013.25 

// 氣壓計 I2C 地址
#define BMP_COUNT 2
#define BMP_I2C_ADDRESS_1 0x76 
#define BMP_I2C_ADDRESS_2 0x77 

// 伺服馬達腳位設置
#define SERVO_COUNT 3
#define SERVO_PIN_1 26
#define SERVO_PIN_2 25
#define SERVO_PIN_3 33

#endif  // CONFIG_H
