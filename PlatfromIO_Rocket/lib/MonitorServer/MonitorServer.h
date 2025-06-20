#pragma once

#include "Constant.h"

#include <SPIFFS.h>
#include <WebServer.h>
#include <ArduinoJson.h>

class MonitorServer {
private:
    static WebServer server;
    
public:
    bool begin();
    static void handleRoot();
    static void handleData();
    void handleClient();
};