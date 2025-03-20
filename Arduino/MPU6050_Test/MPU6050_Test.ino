#include <Wire.h>
#include <MPU6050.h>

class Accelerometer {
private:

    MPU6050 mpu;
    static constexpr int N = 10;  // 取最近 10 次讀數平均
    float accel_buf[N][3] = {0};  // ax, ay, az
    float gyro_buf[N][3] = {0};  // gx, gy, gz
    int index = 0;

    float getAverage(int axis, float buf[][3]);  // 獲取平滑平均值

public:

    bool begin();  // 用於初始化 MPU6050 和檢查連接
    void update(float accelOut[3], float gyroOut[3]);  // 用來更新加速度數據
};

float Accelerometer::getAverage(int axis, float buf[][3]) {
    float sum = 0;
    for (int i = 0; i < N; i++) {sum += buf[i][axis];}
    return sum / N;
}

bool Accelerometer::begin() {
    mpu.initialize();
    if (!mpu.testConnection()) {
        Serial.println("MPU6050 連接失敗！");
        return false;  // 返回錯誤狀態
    }
    return true;  // 返回初始化成功狀態
}

void Accelerometer::getData(float accelOut[3], float gyroOut[3]) {
    int16_t accel[3];
    int16_t gyro[3];

    mpu.getAcceleration(&accel[0], &accel[1], &accel[2]);
    mpu.getRotation(&gyro[0], &gyro[1], &gyro[2]);

    for (int i = 0; i < 3; i++) {
        accel_buf[index][i] = accel[i] / 16384.0;
        gyro_buf[index][i] = gyro[i] / 131.0;
    }

    index = (index + 1) % N;  // 更新索引

    for (int i = 0; i < 3; i++) {
        accelOut[i] = getAverage(i, accel_buf);
        gyroOut[i] = getAverage(i, gyro_buf);
    }
}

Accelerometer imu;  // 創建 IMU 物件

void setup() {
    Serial.begin(115200);
    Wire.begin();

    if (!imu.begin()) {
        Serial.println("MPU6050 初始化失敗！");
        while (1);  // 停止執行
    }
}

void loop() {
    float accel[3], gyro[3];

    imu.getData(accel, gyro);

    Serial.printf("Accel (g)  : X=%+6.2f, Y=%+6.2f, Z=%+6.2f\n", accel[0], accel[1], accel[2]);
    Serial.printf("Gyro (°/s) : X=%+6.2f, Y=%+6.2f, Z=%+6.2f\n", gyro[0], gyro[1], gyro[2]);

    delay(100);
}