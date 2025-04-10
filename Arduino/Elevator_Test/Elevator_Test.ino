#include "Barometer.h"
#include "Accelerometer.h"
#include "ParachuteSystem.h"

#include <SD.h>
#include <SPI.h>

#define BMP390_I2C_ADDRESS_1 0x76
#define BMP390_I2C_ADDRESS_2 0x77
#define STANDARD_PRESSURE_1 1009.40
#define STANDARD_PRESSURE_2 1009.63

const int chipSelect = 5;  // SD 卡模組的 Chip Select 腳位，根據你的接線修改

BMPController bmpController_1(BMP390_I2C_ADDRESS_1, STANDARD_PRESSURE_1);
BMPController bmpController_2(BMP390_I2C_ADDRESS_2, STANDARD_PRESSURE_2);

Accelerometer accel;

ParachuteSystem parachuteSystem;

void setup() {
    Serial.begin(115200);  // 初始化串口通信
    Wire.begin(SDA_PIN, SCL_PIN);

    if (!bmpController_1.begin()) {
        Serial.println("BMP390 1 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    if (!bmpController_2.begin()) {
        Serial.println("BMP390 2 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    if (!accel.begin(&Wire)) {
        Serial.println("Could not find MPU9250");
        while (1);
    }

    if (!SD.begin(chipSelect)) {
        Serial.println("SD 卡初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    Serial.println("初始化成功！");
}

void loop() {
    float temperature_1, pressure_1, altitude_1;
    float temperature_2, pressure_2, altitude_2;
    float acc[3], gyro[3], mag[3], aSqrt, mD;
    bool is_bmp_1, is_bmp_2, is_acc;

    unsigned long long now = millis();  // 時間戳記（ms）

    is_bmp_1 = bmpController_1.getData(temperature_1, pressure_1, altitude_1);
    is_bmp_2 = bmpController_2.getData(temperature_2, pressure_2, altitude_2);
    is_acc = accel.getData(acc, gyro, mag, aSqrt, mD);

    float current_altitude;
    if (is_bmp_1 && is_bmp_2) {
        current_altitude = (altitude_1 + altitude_2) / 2.0;
    } else if (is_bmp_1) {
        current_altitude = altitude_1;
    } else if (is_bmp_2) {
        current_altitude = altitude_2;
    } else {
        current_altitude = -1.0; // 代表無法取得高度
    }

    float slope, sub_slope;
    parachuteSystem.calculateSlope(now, current_altitude, slope, sub_slope);

    File dataFile = SD.open("/data.csv", FILE_APPEND);
    if (dataFile) {
        Serial.print("Time: "); Serial.print(now); Serial.print(", ");
        Serial.print("Altitude 1: "); Serial.print(altitude_1); Serial.print(", ");
        Serial.print("Altitude 2: "); Serial.print(altitude_2); Serial.print(", ");
        Serial.print("Current Altitude: "); Serial.print(current_altitude); Serial.print(", ");
        Serial.print("Slope: "); Serial.print(slope); Serial.print(", ");
        Serial.print("Sub Slope: "); Serial.print(sub_slope); Serial.print(", ");
        Serial.print("aSqrt: "); Serial.println(acc[2]);
        
        dataFile.print(now); dataFile.print(",");
        dataFile.print(altitude_1); dataFile.print(",");
        dataFile.print(altitude_2); dataFile.print(",");
        dataFile.print(current_altitude); dataFile.print(",");
        dataFile.print(slope); dataFile.print(",");
        dataFile.print(sub_slope); dataFile.print(",");
        dataFile.println(acc[2]);
        dataFile.close();
    } else {
        Serial.println("無法寫入 SD 卡");
    }

    delay(100);
}