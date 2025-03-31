#include "Barometer.h"

BMPController::BMPController(uint8_t address, float pressure)
    : i2cAddress(address), std_pressure(pressure) {}

bool BMPController::begin() {

    if (!bmp.begin(i2cAddress)) {  // 初始化 BMP280
        Serial.println("BMP280 初始化失敗！");
        return false;
    }
    
    bmp.setSampling(
        Adafruit_BMP280::MODE_FORCED,   // 測量一次後進入休眠，節省功耗 (NORMAL 模式下可連續測量)
        Adafruit_BMP280::SAMPLING_X2,   // 溫度採樣倍率 (X1 ~ X16，數值越大精度越高)
        Adafruit_BMP280::SAMPLING_X16,  // 氣壓採樣倍率 (X1 ~ X16)
        Adafruit_BMP280::FILTER_X16,    // 濾波強度 (OFF, X2, X4, X8, X16)
        Adafruit_BMP280::STANDBY_MS_1   // NORMAL 模式下的休眠時間 (1 ~ 4000ms，FORCED 模式無效)
    );
    
    Serial.println("BMP280 初始化成功！");
    return true;
}

bool BMPController::getData(float &temperature, float &pressure, float &altitude) {

    bmp.takeForcedMeasurement();

    temperature = bmp.readTemperature();
    pressure = bmp.readPressure() / 100.0F;  // 轉換為 hPa
    altitude = bmp.readAltitude(1013.25);  // 設定標準氣壓 1013.25 hPa

    if (isnan(temperature) || isnan(pressure) || isnan(altitude)) {
        Serial.println("氣壓計數據丟失");
        return false;
    }

    return true;
}