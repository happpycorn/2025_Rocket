#include "Constant.h"
#include "HFreqSensor.h"
#include "BMPController.h"

const float STANDARD_PRESSURE_1 = 1013.25;
const float STANDARD_PRESSURE_2 = 1013.25;

BMPController bmp1(BMP_I2C_ADDRESS_1, STANDARD_PRESSURE_1, 0);
BMPController bmp2(BMP_I2C_ADDRESS_2, STANDARD_PRESSURE_2, 3);

void setup() {
    Serial.begin(115200);

    if (!bmp1.begin()) {
        Serial.println("BMP390 1 初始化失敗！");
        while (1);
    }

    if (!bmp1.begin()) {
        Serial.println("BMP390 2 初始化失敗！");
        while (1);
    }

    Serial.println("BMP390 初始化成功！");
}

void loop() {
    float data[6];
    bool succ[2] = {bmp1.getData(data), bmp2.getData(data)};

    if (succ[0] && succ[1]) {
        Serial.print("T: "); Serial.print(data[0]); Serial.print(" °C, ");
        Serial.print("P: "); Serial.print(data[1]); Serial.print(" hPa, ");
        Serial.print("A: "); Serial.print(data[2]); Serial.println(" meters");
        Serial.print("T: "); Serial.print(data[3]); Serial.print(" °C, ");
        Serial.print("P: "); Serial.print(data[4]); Serial.print(" hPa, ");
        Serial.print("A: "); Serial.print(data[5]); Serial.println(" meters");
        Serial.println("=========");  // 輸出空行
    } else {
        Serial.println("獲取數據失敗！");
    }

    delay(100);
}