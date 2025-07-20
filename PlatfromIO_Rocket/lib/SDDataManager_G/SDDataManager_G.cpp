#include "SDDataManager_G.h"

bool SDDataManager::begin() {
    if (!SD.begin(SD_CS_PIN)) return false;
    if (SD.exists(path)) return true;

    File file = SD.open(path, FILE_WRITE);
    if (!file) return false;
    
    // 寫入欄位名稱
    for (const char* label : labels) file_print(file, label);
    for (int i = 0; i < BOOL_DATA_LEN; i++) {
        file.print("rocket_state_"); file.print(i); file.print(",");
    }
    for (int i = 0; i < GPS_FLOAT_DATA_LEN; i++) {
        file.print("local_gps_data_"); file.print(i); 
        if (i < GPS_FLOAT_DATA_LEN - 1) file.print(',');
    }

    file.println();
    file.close();

    return true;
}

bool SDDataManager::saveData(const RecordData &data) {
    File file = SD.open(path, FILE_APPEND);
    if (!file) return false;

    // 寫入 time 與系統狀態
    file_print(file, data.time);
    file_print(file, data.slope_index);
    file_print(file, data.warning_index);
    file_print(file, data.slope_overflow);
    file_print(file, data.warning_overflow);
    
    // Data - slope_data[SLOPE_INDEX_MAX][4]
    for (int i = 0; i < 4; i++) file_print(file, data.slope_data[data.slope_index][i]);

    // attit_data[3]
    for (int i = 0; i < 3; i++) file_print(file, data.attit_data[i]);

    // gps_data_d[DOUBLE_DATA_LEN]
    for (int i = 0; i < DOUBLE_DATA_LEN; i++) file_print(file, data.gps_data_d[i]);

    // LoRa
    file_print(file, data.last_recive_time);
    file_print(file, data.recive_pack_count);

    // rocket_state[BOOL_DATA_LEN]
    for (int i = 0; i < BOOL_DATA_LEN; i++) file_print(file, data.rocket_state[i]);

    // local_gps_data_f[GPS_FLOAT_DATA_LEN]
    for (int i = 0; i < GPS_FLOAT_DATA_LEN; i++) file_print(file, data.local_gps_data_f[i], i == GPS_FLOAT_DATA_LEN - 1);
    
    file.println();
    file.close();

    File warningfile = SD.open(warning_path, FILE_APPEND);
    if (!warningfile) return false;
    while (warning_index != data.warning_index) {
        warningfile.println(data.warning[warning_index]);
        warning_index = (warning_index+1)%WARNING_INDEX_MAX;
    }

    return true;
}
