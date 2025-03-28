#include <Adafruit_BMP280.h>

class BMPController {
public:

    BMPController(uint8_t address, float std_pressure);

    bool begin();
    bool getData(float &temperature, float &pressure, float &altitude);

private:

    Adafruit_BMP280 bmp;
    uint8_t i2cAddress;   // I2C 地址
    float std_pressure;
};

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
    altitude = bmp.readAltitude(std_pressure);  // 設定標準氣壓 1013.25 hPa

    if (isnan(temperature) || isnan(pressure) || isnan(altitude)) {
        Serial.println("數據無效，感測器可能未初始化或發生錯誤！");
        return false;
    }

    return true;
}

#include <Wire.h>

#define BMP280_I2C_ADDRESS_1 0x76
#define BMP280_I2C_ADDRESS_2 0x77
#define STANDARD_PRESSURE 1015.00
#define SAMPLE_INTERVAL 100000  // 10Hz, 100000 微秒 (100ms)

BMPController bmp1(BMP280_I2C_ADDRESS_1, STANDARD_PRESSURE);
BMPController bmp2(BMP280_I2C_ADDRESS_2, STANDARD_PRESSURE);

void setup() {
    Serial.begin(115200);
    
    if (!bmp1.begin()) {
        Serial.println("BMP280 #1 初始化失敗！");
        while (1);
    }
    if (!bmp2.begin()) {
        Serial.println("BMP280 #2 初始化失敗！");
        while (1);
    }
    Serial.println("BMP280 初始化成功！");
}

static uint64_t nextSampleTime = 0;  // 使用 64-bit 儲存
void loop() {
    uint64_t now = micros();  // 直接使用 64-bit

    // 使用 while 來塞住，直到下一次取樣時間
    while (now < nextSampleTime) {
        now = micros();  // 更新時間
    }

    nextSampleTime += SAMPLE_INTERVAL;

    float temp1, press1, alt1;
    float temp2, press2, alt2;

    if (bmp1.getData(temp1, press1, alt1) && bmp2.getData(temp2, press2, alt2)) {
        Serial.print(now);
        Serial.print(",");
        Serial.print(temp1);
        Serial.print(",");
        Serial.print(press1);
        Serial.print(",");
        Serial.print(alt1);
        Serial.print(",");
        Serial.print(temp2);
        Serial.print(",");
        Serial.print(press2);
        Serial.print(",");
        Serial.print(alt2);
        Serial.println();
    } else {
        Serial.println("獲取數據失敗！");
    }
}
