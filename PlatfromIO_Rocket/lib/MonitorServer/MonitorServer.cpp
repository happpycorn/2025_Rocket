#include "MonitorServer.h"

WebServer MonitorServer::server(80);

bool MonitorServer::begin() {
    
    if (!SPIFFS.begin(true)) {
        return false;
    }

    server.on("/", handleRoot);
    server.on("/data", handleData);
    server.begin();
    return true;
}

void MonitorServer::handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void MonitorServer::handleData() {

    extern RecordData data;
    extern portMUX_TYPE dataMux;
    JsonDocument doc;
    RecordData current;                    // 宣告一份副本
    portENTER_CRITICAL(&dataMux);
    current = data;                        // 將共享變數 data 複製到副本
    portEXIT_CRITICAL(&dataMux);

    doc["time"] = data.time;

    int count_slope = data.slope_overflow ? SLOPE_INDEX_MAX : data.slope_index;
    JsonArray slope = doc["slope_data"].to<JsonArray>();
    for (int i = 0; i < count_slope; i++) {
        JsonArray row = slope.add<JsonArray>();
        for (int j = 0; j < 4; j++) {
            row.add(data.slope_data[(i+data.slope_index)%SLOPE_INDEX_MAX][j]);
        }
    }

    JsonArray attit = doc["attit_data"].to<JsonArray>();
    for (int i = 0; i < 3; i++) attit.add(data.attit_data[i]);

    JsonArray rocket = doc["rocket_state"].to<JsonArray>();
    for (int i = 0; i < 12; i++) rocket.add(data.rocket_state[i]);

    JsonArray gps = doc["gps_data"].to<JsonArray>();
    for (int i = 0; i < 4; i++) gps.add(data.gps_data_d[i]);

    doc["recive_pack_count"] = data.recive_pack_count;
    doc["last_recive_time"] = data.last_recive_time;

    int count_warning = data.warning_overflow ? WARNING_INDEX_MAX : data.warning_index;
    JsonArray warn = doc["warning"].to<JsonArray>();
    for (int i = 0; i < count_warning; i++) warn.add(data.warning[(i+data.warning_index)%WARNING_INDEX_MAX]);

    String json;
    serializeJson(doc, json);
    server.send(200, "application/json", json);
}

void MonitorServer::handleClient() {
    server.handleClient();
}