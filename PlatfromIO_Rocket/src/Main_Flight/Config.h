#pragma once

constexpr int LAUNCH_1_UPPER_BOUND = 1500;
constexpr int LAUNCH_2_UPPER_BOUND = 300;

constexpr float STANDARD_PRESSURE_1 = 1007.05;
constexpr float STANDARD_PRESSURE_2 = 1007.36;

constexpr int SERVO_PIN_1 = 32;
constexpr int SERVO_PIN_2 = 33;
constexpr int SERVO_PIN_3 = 25;

#include "Constant.h"
#include "DataBuffer.h"
#include "GPSModule.h"
#include "Hygrometer.h"
#include "BMPController.h"
#include "ServoController.h"
#include "SDDataManager_F.h"
#include "LoRaDataSender.h"
#include "ParachuteSystem.h"
#include "Accelerometer-9250.h"