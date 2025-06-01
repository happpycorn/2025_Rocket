#include "Barometer.h"

BMPController::BMPController(uint8_t address, float pressure)
    : i2cAddress(address), std_pressure(pressure) {}

bool BMPController::begin() {

    if (!bmp.begin_I2C(i2cAddress)) {  // 初始化 BMP280
        return false;
    }

    bmp.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_16X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_200_HZ);

    return true;
}

bool BMPController::getData(float &temperature, float &pressure, float &altitude) {

    if (!bmp.performReading()) {
        return false;
    }

    temperature = bmp.readTemperature();
    pressure = bmp.readPressure() / 100.0F;  // 轉換為 hPa
    altitude = bmp.readAltitude(std_pressure);  // 設定標準氣壓 1013.25 hPa

    return true;
}