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


#define BMP280_I2C_ADDRESS 0x76
#define STANDARD_PRESSURE 1013.25

BMPController bmpController(BMP280_I2C_ADDRESS, STANDARD_PRESSURE);

void setup() {
    Serial.begin(115200);  // 初始化串口通信

    // 初始化 BMP280 感測器
    if (!bmpController.begin()) {
        Serial.println("BMP280 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    Serial.println("BMP280 初始化成功！");
}

void loop() {
    float temperature, pressure, altitude;

    // 獲取數據
    if (bmpController.getData(temperature, pressure, altitude)) {
        Serial.print("Temperature: ");
        Serial.print(temperature);
        Serial.println(" °C");

        Serial.print("Pressure: ");
        Serial.print(pressure);
        Serial.println(" hPa");

        Serial.print("Altitude: ");
        Serial.print(altitude);
        Serial.println(" meters");

        Serial.println();  // 輸出空行
    } else {
        Serial.println("獲取數據失敗！");
    }

    delay(100);
}