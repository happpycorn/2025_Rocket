#include "MonitorServer.h"

WebServer MonitorServer::server(80);
RecordData MonitorServer::current;

void MonitorServer::handleData() {

    extern RecordData data;
    extern portMUX_TYPE dataMux;
    JsonDocument doc;
    portENTER_CRITICAL(&dataMux);
    current = data;                        // 將共享變數 data 複製到副本
    portEXIT_CRITICAL(&dataMux);

    doc["time"] = current.time;

    int count_slope = current.slope_overflow ? SLOPE_INDEX_MAX : SLOPE_INDEX_MAX-current.slope_index;
    JsonArray slope = doc["slope_data"].to<JsonArray>();
    for (int i = 0; i < count_slope; i++) {
        JsonArray row = slope.add<JsonArray>();
        for (int j = 0; j < 4; j++) {
            row.add(current.slope_data[(i+current.slope_index)%SLOPE_INDEX_MAX][j]);
        }
    }

    JsonArray attit = doc["attit_data"].to<JsonArray>();
    for (int i = 0; i < 3; i++) attit.add(current.attit_data[i]);

    JsonArray rocket = doc["rocket_state"].to<JsonArray>();
    for (int i = 0; i < 12; i++) rocket.add(current.rocket_state[i]);

    JsonArray gps = doc["gps_data"].to<JsonArray>();
    for (int i = 0; i < 4; i++) gps.add(current.gps_data_d[i]);
    
    doc["max_alt"] = current.max_alt;

    doc["recive_pack_count"] = current.recive_pack_count;
    doc["last_recive_time"] = current.last_recive_time;

    int count_warning = current.warning_overflow ? WARNING_INDEX_MAX : WARNING_INDEX_MAX-current.warning_index;
    JsonArray warn = doc["warning"].to<JsonArray>();
    for (int i = 0; i < count_warning; i++) warn.add(current.warning[(i+current.warning_index)%WARNING_INDEX_MAX]);

    String json;
    serializeJson(doc, json);
    server.send(200, "application/json", json);
}

bool MonitorServer::begin() {
    
    if (!SPIFFS.begin(true)) { return false; }

    server.serveStatic("/", SPIFFS, "/index.html");
    server.serveStatic("/asset/", SPIFFS, "/asset/");
    server.serveStatic("/styles/", SPIFFS, "/styles/");
    server.serveStatic("/scripts/", SPIFFS, "/scripts/");
    server.on("/data", HTTP_GET, handleData);
    server.begin();

    return true;
}

void MonitorServer::handleClient() {
    server.handleClient();
}