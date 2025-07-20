#pragma once

constexpr const char* SSID = "ESP32_Receiver";
constexpr const char* PASSWORD = "00000000";

#include <WiFi.h>

#include "Constant.h"
#include "GPSModule.h"
#include "MonitorServer.h"
#include "SDDataManager_G.h"
#include "LoRaDataReciver.h"
#include "ServoController.h"