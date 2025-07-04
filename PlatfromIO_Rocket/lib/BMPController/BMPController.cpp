#include "BMPController.h"

bool BMPController::begin() {

    if (!bmp.begin_I2C(iicAddr)) {  // 初始化 BMP280
        return false;
    }

    bmp.setTemperatureOversampling(BMP3_NO_OVERSAMPLING);
    bmp.setPressureOversampling(BMP3_OVERSAMPLING_16X);
    bmp.setIIRFilterCoeff(BMP3_IIR_FILTER_COEFF_3);
    bmp.setOutputDataRate(BMP3_ODR_200_HZ);

    return true;
}

bool BMPController::getData(float data[]) {

    if (!bmp.performReading()) {
        return false;
    }

    data[data_addr] = bmp.readTemperature();
    data[data_addr+1] = bmp.readPressure() / 100.0F;  // 轉換為 hPa
    data[data_addr+2] = bmp.readAltitude(std_pressure);  // 設定標準氣壓 1013.25 hPa

    return true;
}