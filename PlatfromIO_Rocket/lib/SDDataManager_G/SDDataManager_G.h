#pragma once

#include "Constant.h"
#include <SPI.h>
#include <SD.h>

class SDDataManager {
public:
    bool begin();
    bool saveData(const RecordData &data);

private:
    const char* path = "/ground_data.csv";
    const char* warning_path = "/warning_data.txt";

    const char* labels[19] = {
        "time", "slope_index", "warning_index", "slope_overflow", "warning_overflow",
        "slope_data_0", "slope_data_1", "slope_data_2", "slope_data_3",
        "attit_roll", "attit_pitch", "attit_yaw",
        "gps_latitude", "gps_longitude",
        "self_gps_latitude", "self_gps_longitude",
        "max_alt", "last_receive_time", "receive_pack_count"
    };

    template<typename T>
    void file_print(Stream &file, T value, bool end = false) {
        file.print(value);
        if (!end) file.print(',');
    }

    void file_print(Stream &file, float value, bool end = false) {
        file.print(value, 6);
        if (!end) file.print(',');
    }

    void file_print(Stream &file, double value, bool end = false) {
        file.print(value, 8);
        if (!end) file.print(',');
    }

    int warning_index = 0;
};
