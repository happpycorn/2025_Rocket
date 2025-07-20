#pragma once

#include "Constant.h"
#include <SPI.h>
#include <SD.h>

class SDDataManager {
public:
    bool begin();
    bool saveData(const LFreqData &data);

private:
    int index = 0;

    const char* f_labels[LF_FLOAT_DATA_LEN] = {
        "BMP1_Temp", "BMP1_Pressure", "BMP1_Altitude",
        "BMP2_Temp", "BMP2_Pressure", "BMP2_Altitude",
        "Slope_X", "Slope_Y", "Slope_Z",
        "Acc_X1", "Acc_Y1", "Acc_Z1",
        "Acc_X2", "Acc_Y2", "Acc_Z2",
        "Acc_X3", "Acc_Y3", "Acc_Z3",
        "Acc_X4", "Acc_Y4", "Acc_Z4",
        "Gyro_X", "Gyro_Y",
        "GPS_0", "GPS_1", "GPS_2", "GPS_3", "GPS_4", "GPS_5",
        "GPS_6", "GPS_7", "GPS_8", "GPS_9", "GPS_10"
    };

    const char* b_labels[LF_BOOL_DATA_LEN] = {
        "Servo_1", "Servo_2", "Servo_3",
        "Fail_1", "Fail_2",
        "Sensor_1", "Sensor_2", "Sensor_3", "Sensor_4",
        "Is_HF_Data", "Is_GPS_Data"
    };

    const char* d_labels[LF_DOUBLE_DATA_LEN] = {
        "GPS_Latitude", "GPS_Longitude"
    };
};
