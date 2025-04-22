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
    Wire.begin(SDA_PIN, SCL_PIN);
    mpu.setWire(&Wire);

    mpu.beginAccel();
    mpu.beginGyro();
    mpu.beginMag();

    // You can set your own offset for mag values
    // mpu.magXOffset = -50;
    // mpu.magYOffset = -55;
    // mpu.magZOffset = -10;

    return true;
}

bool Accelerometer::getData(float data[]) {

    uint8_t sensorId;
    int result;

    result = mpu.readId(&sensorId);
    if (result != 0) {
        for (int i = 0; i < 3; i++) {
            data[data_addr+i] = 0.0;
            data[data_addr+i+3] = 0.0;
            data[data_addr+i+6] = 0.0;
        }
        return false;
    }

    bool success = true;

    // 加速度
    result = mpu.accelUpdate();
    if (result == 0) {
        data[data_addr] = mpu.accelX();
        data[data_addr+1] = mpu.accelY();
        data[data_addr+2] = mpu.accelZ();
        data[data_addr+9] = mpu.accelSqrt();
    } else {
        for (int i = 0; i < 3; i++) { data[data_addr+i] = 0.0; }
        data[data_addr+9] = 0.0;
        success = false;
    }

    // 角速度
    result = mpu.gyroUpdate();
    if (result == 0) {
        data[data_addr+3] = mpu.gyroX();
        data[data_addr+4] = mpu.gyroY();
        data[data_addr+5] = mpu.gyroZ();
    } else {
        for (int i = 0; i < 3; i++) { data[data_addr+i+3] = 0.0; }
        success = false;
    }

    // 磁力計
    result = mpu.magUpdate();
    if (result != 0) {
        mpu.beginMag();
        result = mpu.magUpdate();
    }
    if (result == 0) {
        data[data_addr+6] = mpu.magX();
        data[data_addr+7] = mpu.magY();
        data[data_addr+8] = mpu.magZ();
        data[data_addr+10] = mpu.magHorizDirection();
    } else {
        for (int i = 0; i < 3; i++) { data[data_addr+i+6] = 0.0; }
        data[data_addr+10] = 0.0;
        success = false;
    }

    return success;
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