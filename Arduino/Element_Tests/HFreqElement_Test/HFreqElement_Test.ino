#include "HFreqSensor.h"

// 初始化：兩顆 BMP390，標準氣壓皆設為 1013.25 hPa
BMPController bmp1(0x76, 1013.25, 0);     // data[0~2]
BMPController bmp2(0x77, 1013.25, 3);     // data[3~5]

Accelerometer accel(6);                  // data[6~16]
Hygrometer hygro(20);                    // data[20~21]

float sensorData[32];  // 確保足夠儲存所有欄位

void setup() {
    Serial.begin(115200);
    delay(2000);
    Serial.println("初始化感測器...");

    bool ok1 = bmp1.begin();
    bool ok2 = bmp2.begin();
    bool ok3 = accel.begin();
    bool ok4 = hygro.begin();

    Serial.println(ok1 ? "BMP1 初始化成功" : "BMP1 初始化失敗");
    Serial.println(ok2 ? "BMP2 初始化成功" : "BMP2 初始化失敗");
    Serial.println(ok3 ? "MPU 初始化成功" : "MPU 初始化失敗");
    Serial.println(ok4 ? "SHTC3 初始化成功" : "SHTC3 初始化失敗");
}

void loop() {
    Serial.println("讀取感測器資料...");

    bool bmp1Ok = bmp1.getData(sensorData);
    bool bmp2Ok = bmp2.getData(sensorData);
    bool accelOk = accel.getData(sensorData);
    bool hygroOk = hygro.getData(sensorData);

    Serial.println("---- BMP1 ----");
    if (bmp1Ok) {
        Serial.print("Temp: "); Serial.print(sensorData[0]); Serial.println(" C");
        Serial.print("Pres: "); Serial.print(sensorData[1]); Serial.println(" hPa");
        Serial.print("Alti: "); Serial.print(sensorData[2]); Serial.println(" m");
    } else {
        Serial.println("BMP1 讀取失敗");
    }

    Serial.println("---- BMP2 ----");
    if (bmp2Ok) {
        Serial.print("Temp: "); Serial.print(sensorData[3]); Serial.println(" C");
        Serial.print("Pres: "); Serial.print(sensorData[4]); Serial.println(" hPa");
        Serial.print("Alti: "); Serial.print(sensorData[5]); Serial.println(" m");
    } else {
        Serial.println("BMP2 讀取失敗");
    }

    Serial.println("---- MPU ----");
    if (accelOk) {
        Serial.print("Accel: ");
        Serial.print(sensorData[6]); Serial.print(", ");
        Serial.print(sensorData[7]); Serial.print(", ");
        Serial.print(sensorData[8]); Serial.println(" m/s^2");

        Serial.print("Gyro: ");
        Serial.print(sensorData[9]); Serial.print(", ");
        Serial.print(sensorData[10]); Serial.print(", ");
        Serial.print(sensorData[11]); Serial.println(" deg/s");

        Serial.print("Mag: ");
        Serial.print(sensorData[12]); Serial.print(", ");
        Serial.print(sensorData[13]); Serial.print(", ");
        Serial.print(sensorData[14]); Serial.println(" uT");

        Serial.print("Accel Magnitude: "); Serial.println(sensorData[15]);
        Serial.print("Mag Direction: "); Serial.println(sensorData[16]);
    } else {
        Serial.println("MPU 讀取失敗");
    }

    Serial.println("---- SHTC3 ----");
    if (hygroOk) {
        Serial.print("Humidity: "); Serial.print(sensorData[20]); Serial.println(" %");
        Serial.print("Temperature: "); Serial.print(sensorData[21]); Serial.println(" C");
    } else {
        Serial.println("SHTC3 讀取失敗");
    }

    Serial.println("============================\n");
    delay(1000);  // 每秒讀取一次
}
