#include "Config.h"

ServoController myServo(SERVO_PIN);

BMPController bmp_1(BMP390_I2C_ADDRESS_1, STANDARD_PRESSURE_1);
BMPController bmp_2(BMP390_I2C_ADDRESS_2, STANDARD_PRESSURE_2);

ParachuteSystem prcSystem;

Accelerometer accel;
Hygrometer hgyro;

void setup() {
    Serial.begin(115200);  // 初始化串口通信
    Serial.println("程式開始！");

    Wire.begin(SDA_PIN, SCL_PIN);

    myServo.begin();

    if (!bmp_1.begin()) {
        Serial.println("BMP390 1 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    if (!bmp_2.begin()) {
        Serial.println("BMP390 2 初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    if (!SD.begin(SD_CS)) {
        Serial.println("SD 卡初始化失敗！");
        while (1);  // 如果初始化失敗，停在這裡
    }

    if (!accel.begin(&Wire)) {
        Serial.println("Could not find MPU9250");
        while (1);
    }

    if (!hgyro.begin()) {
        Serial.println("SHTC3 初始化失敗！");
        while (1);
    }

    int fillCount = BUFFER_SIZE*2;
    float t1, p1, a1, t2, p2, a2;
    unsigned long long now;
    for (int i = 0; i < fillCount; i++) {
        now = millis();
        bmp_1.getData(t1, p1, a1);
        bmp_2.getData(t2, p2, a2);
        prcSystem.fillSpace(now, (a1 + a2) / 2.0);
    }

    Serial.println("初始化成功！");
}

void loop() {
    // 0~5 BMP, 6~8 Slope, 9~10 Acc, 11~12 Hgyro
    float data[13];
    unsigned long long now = millis();  // 時間戳記（ms）

    bmp_1.getData(data[0], data[1], data[2]);
    bmp_2.getData(data[3], data[4], data[5]);
    data[6] = (data[2] + data[5]) / 2.0;

    prcSystem.calculateSlope(now, data[6], data[7], data[8]);

    bool isLaunch;
    prcSystem.decideDeployment(data[6], data[7], isLaunch);
    myServo.setServoAngle(isLaunch);

    float acc[3], gyro[3], mag[3];
    accel.getData(acc, gyro, mag, data[9], data[10]);

    hgyro.getData(data[11], data[12]);

    File dataFile = SD.open("/data.csv", FILE_APPEND);
    if (dataFile) {
        Serial.print("Time: "); Serial.print(now); Serial.print(", ");
        Serial.print("Current Altitude: "); Serial.print(data[6]); Serial.print(", ");
        Serial.print("Slope: "); Serial.print(data[7]); Serial.print(", ");
        Serial.print("Sub Slope: "); Serial.print(data[8]); Serial.print(", ");
        Serial.print("Open: "); Serial.println(isLaunch);

        dataFile.print(now); dataFile.print(",");
        
        for (int i = 0; i < 13; i++) {
            dataFile.print(data[i]); dataFile.print(",");
        }
        for (int i = 0; i < 3; i++) {
            dataFile.print(acc[i]); dataFile.print(",");
            dataFile.print(gyro[i]); dataFile.print(",");
            dataFile.print(mag[i]); dataFile.print(",");
        }

        dataFile.println(isLaunch);
        dataFile.close();
    } else {
        Serial.println("無法寫入 SD 卡");
    }

    delay(100);
}
