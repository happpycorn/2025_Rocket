#pragma once

constexpr int LAUNCH_1_UPPER_BOUND = 1500;
constexpr int LAUNCH_2_UPPER_BOUND = 300;

constexpr float STANDARD_PRESSURE_1 = 1003.39;
constexpr float STANDARD_PRESSURE_2 = 1003.45;

#include "Constant.h"
#include "DataBuffer_Debug.h"
#include "GPSModule.h"
#include "Hygrometer.h"
#include "BMPController.h"
#include "ServoController.h"
#include "SDDataManager_F.h"
#include "LoRaDataSender.h"
#include "ParachuteSystem.h"
#include "Accelerometer-9250.h"