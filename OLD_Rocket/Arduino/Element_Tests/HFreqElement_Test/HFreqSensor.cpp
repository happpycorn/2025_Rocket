#include "HFreqSensor.h"

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

bool Accelerometer::begin() {
    // 驗證 WHO_AM_I
    uint8_t id = readRegister(MPU_ADDR, WHO_AM_I);

    // 喚醒 MPU-6500
    writeRegister(MPU_ADDR, PWR_MGMT_1, 0x00);

    return id == 0x70 || id == 0x73;
}

bool Accelerometer::getData(float data[]) {
    bool success = true;

    // 讀加速度
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(ACCEL_XOUT_H);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6);
    if (Wire.available() == 6) {
        for (int i = 0; i < 3; i++) {
            int16_t raw = (Wire.read() << 8) | Wire.read();
            data[data_addr+i] = (float)raw;
        }
    } else { success = false; }

    // 讀陀螺儀
    Wire.beginTransmission(MPU_ADDR);
    Wire.write(GYRO_XOUT_H);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU_ADDR, 6);
    if (Wire.available() == 6) {
        for (int i = 0; i < 3; i++) {
            int16_t raw = (Wire.read() << 8) | Wire.read();
            data[data_addr+i+3] = (float)raw;
        }
    } else { success = false; }

    for (int i = 0; i < 3; i++) data[data_addr+i+6] = 0.0;
    data[data_addr+9] = 0.0;
    data[data_addr+10] = 0.0;

    return success;
}

uint8_t Accelerometer::readRegister(uint8_t addr, uint8_t reg) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.endTransmission(false);
    Wire.requestFrom(addr, 1);
    if (Wire.available()) {
        return Wire.read();
    }
    return 0xFF;
}

void Accelerometer::writeRegister(uint8_t addr, uint8_t reg, uint8_t val) {
    Wire.beginTransmission(addr);
    Wire.write(reg);
    Wire.write(val);
    Wire.endTransmission();
}

bool Hygrometer::begin() {
    return shtc3.begin();
}

bool Hygrometer::getData(float data[]) {
    sensors_event_t h, t;
    bool succ = shtc3.getEvent(&h, &t);
    data[data_addr] = h.relative_humidity;  // 讀取濕度
    data[data_addr+1] = t.temperature;  // 讀取溫度
    return succ;
}