#include "GPSModule.h"

struct GPSData {
    double d[2];
    float f[14];
};

// 初始化一個 GPSData 結構體來存儲 GPS 資料
GPSData data;

GPSModule gps(0);

void setup() {
    Serial.begin(115200);
    
    gps.begin();
}

void loop() {
    gps.getData(data.d, data.f);

    // 輸出經度和緯度
    Serial.print("Latitude: ");
    Serial.println(data.d[0], 6);  // 顯示緯度（6 位小數）
    Serial.print("Longitude: ");
    Serial.println(data.d[1], 6);  // 顯示經度（6 位小數）
    
    // 輸出其他 GPS 資料
    Serial.print("Altitude: ");
    Serial.println(data.f[0], 2);  // 顯示高度（2 位小數）
    Serial.print("Speed: ");
    Serial.println(data.f[1], 2);  // 顯示速度（2 位小數）
    Serial.print("Course: ");
    Serial.println(data.f[2], 2);  // 顯示航向（2 位小數）
    
    Serial.print("Time: ");
    Serial.print(data.f[3], 0);   // 小時
    Serial.print(":");
    Serial.print(data.f[4], 0);   // 分鐘
    Serial.print(":");
    Serial.println(data.f[5], 0); // 秒

    Serial.print("Date: ");
    Serial.print(data.f[6], 0);   // 日
    Serial.print("/");
    Serial.print(data.f[7], 0);   // 月
    Serial.print("/");
    Serial.println(data.f[8], 0); // 年

    // 輸出衛星訊號品質和其他資料
    Serial.print("HDOP: ");
    Serial.println(data.f[9], 2);
    Serial.print("PDOP: ");
    Serial.println(data.f[10], 2);
    Serial.print("Satellites: ");
    Serial.println(data.f[11], 0); // 使用的衛星數量
    Serial.print("Satellites HDOP: ");
    Serial.println(data.f[12], 2);
    Serial.print("Geoid Separation: ");
    Serial.println(data.f[13], 2);

    delay(1000);  // 每秒打印一次
}
