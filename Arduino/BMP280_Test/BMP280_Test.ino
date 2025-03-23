#include <Adafruit_BMP280.h>

class BMP280Controller {
public:

    BMP280Controller(uint8_t address) : i2cAddress(address) {}

    bool begin();
    bool getData(float &temperature, float &pressure, float &altitude);

private:

    Adafruit_BMP280 bmp;
    uint8_t i2cAddress;   // I2C 地址
};

bool BMP280Controller::begin() {

    if (!bmp.begin()) {  // 初始化 BMP280
        Serial.println("BMP280 初始化失敗！");
        return false;
    }
    
    bmp.setSampling(
        Adafruit_BMP280::MODE_FORCED,       // 選擇模式
        Adafruit_BMP280::SAMPLING_X2,       // 溫度採集精度
        Adafruit_BMP280::SAMPLING_X16,      // 氣壓採集精度
        Adafruit_BMP280::FILTER_X16,        // 濾波範圍
        Adafruit_BMP280::STANDBY_MS_0       // 採集延遲
    );
    
    Serial.println("BMP280 初始化成功！");
    return true;
}

bool BMP280Controller::getData(float &temperature, float &pressure, float &altitude) {

    temperature = bmp.readTemperature();
    pressure = bmp.readPressure() / 100.0F;  // 轉換為 hPa
    altitude = bmp.readAltitude(1013.25);  // 設定標準氣壓 1013.25 hPa

    if (isnan(temperature) || isnan(pressure) || isnan(altitude)) {
        Serial.println("數據無效，感測器可能未初始化或發生錯誤！");
        return false;
    }

    return true;
}


#define BMP280_I2C_ADDRESS 0x76

BMP280Controller bmpController(BMP280_I2C_ADDRESS);

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