#include <Arduino.h>
#include "GPSModule.h"

GPSModule gps(0);
float f_data[14];
double d_data[2];

void setup() {
    Serial.begin(115200);
    while (!Serial);

    if (!gps.begin()) {
        Serial.println("GPS 初始化失敗！");
        while (1);
    }

    Serial.println("GPS 初始化完成！");
}

void loop() {

    if (gps.getData(d_data, f_data)) {
        Serial.println("✅ GPS 資料有效");
        Serial.print("Lat: "); Serial.println(d_data[0], 6);
        Serial.print("Lng: "); Serial.println(d_data[1], 6);

        Serial.print("Altitude: "); Serial.print(f_data[0]); Serial.println(" m");
        Serial.print("Speed: "); Serial.print(f_data[1]); Serial.println(" km/h");
        Serial.print("Course: "); Serial.print(f_data[2]); Serial.println(" deg");

        Serial.print("Time: ");
        Serial.printf("%02.0f:%02.0f:%02.0f\n", f_data[3], f_data[4], f_data[5]);

        Serial.print("Date: ");
        Serial.printf("%02.0f/%02.0f/%04.0f\n", f_data[6], f_data[7], f_data[8]);

        Serial.print("HDOP: "); Serial.println(f_data[9]);
        Serial.print("Satellites: "); Serial.println(f_data[10]);

        Serial.println("-----------");
    } else {
        Serial.println("⚠️ GPS 資料無效或過時");
    }

    delay(1000);
}
