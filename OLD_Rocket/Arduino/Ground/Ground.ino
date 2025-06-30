#include "Config.h"

LoRaDataReciver lora;
using LoRaResult = LoRaDataReciver::Result;
GPSModule gps(0);
RecordData data;
SDDataManager sd;

const char* ssid = "ESP32_Receiver";
const char* password = "00000000";

WebServer server(80);

void handleRoot() {
    File file = SPIFFS.open("/index.html", "r");
    server.streamFile(file, "text/html");
    file.close();
}

void handleData() {
    data.time = millis();

    float g_f[GPS_FLOAT_DATA_LEN]; double g_d[GPS_DOUBLE_DATA_LEN];
    data.b[LOCAL_GPS_BOOL_ADDR] = gps.getData(g_d, g_f);
    for (int i = LOCAL_GPS_FLOAT_ADDR; i < FLOAT_DATA_LEN; i++) data.f[i] = g_f[i-LOCAL_GPS_FLOAT_ADDR];
    for (int i = LOCAL_GPS_DOUBLE_ADDR; i < DOUBLE_DATA_LEN; i++) data.d[i] = g_d[i-LOCAL_GPS_DOUBLE_ADDR];

    sd.saveData(data);

    StaticJsonDocument<1024> doc;  // 視你要傳的資料大小調整（或用 DynamicJsonDocument）

    // 加入 float 陣列
    JsonArray floats = doc.createNestedArray("f");
    for (int i = 0; i < FLOAT_DATA_LEN; i++) floats.add(data.f[i]);
    // 加入 bool 陣列
    JsonArray bools = doc.createNestedArray("b");
    for (int i = 0; i < BOOL_DATA_LEN; i++) bools.add(data.b[i]);
    // 加入 double 陣列
    JsonArray doubles = doc.createNestedArray("d");
    for (int i = 0; i < DOUBLE_DATA_LEN; i++) doubles.add(data.d[i]);

    String json;
    serializeJson(doc, json);
    server.send(200, "application/json", json);
}

void setup() {
    Serial.begin(115200);       // 給電腦看的 Serial
    lora.begin();
    gps.begin();

    if (!sd.begin()) {
        Serial.println("SD Card Init Fail.");
        while (1);
    }

    // 啟用 SPIFFS
    if (!SPIFFS.begin(true)) {
        Serial.println("SPIFFS init failed!");
        return;
    }

    // 啟用 WiFi AP 模式
    WiFi.softAP(ssid, password);
    Serial.println("AP Started. IP: ");
    Serial.println(WiFi.softAPIP());

    // 設定 HTTP 路由
    server.on("/", handleRoot);
    server.on("/data", handleData);
    server.begin();
}

void loop() {
    LoRaResult r = lora.reciveData();
    if (r.message != nullptr) Serial.println(r.message);
    if (r.data.is_data) {
        data.last_recive_time = millis();
        data.recive_pack_count = r.data.pack_count;
        for (int i = 0; i < RECIVE_FLOAT_DATA_LEN; i++) data.f[i] = r.data.f[i];
        for (int i = 0; i < RECIVE_BOOL_DATA_LEN; i++) data.b[i] = r.data.b[i];
        for (int i = 0; i < RECIVE_DOUBLE_DATA_LEN; i++) data.d[i] = r.data.d[i];
    }

    server.handleClient();
}
