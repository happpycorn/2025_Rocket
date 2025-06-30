#include "SDDataManager_G.h"

SPIClass mySPI(VSPI);

bool SDDataManager::begin() {
    mySPI.begin(21, 19, 18, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN, mySPI)) {  // 假設 SPI 接口的 CS 引腳是 5
        return false;
    }
    return true;
}

bool SDDataManager::saveData(const RecordData &data) {
    File file = SD.open("/reciveData.bin", FILE_APPEND);
    if (!file) return false;

    // Sys
    file.write((uint8_t*)&data.time, sizeof(data.time));
    file.write((uint8_t*)&data.slope_index, sizeof(data.slope_index));
    file.write((uint8_t*)&data.warning_index, sizeof(data.warning_index));
    file.write((uint8_t*)&data.slope_overflow, sizeof(data.slope_overflow));
    file.write((uint8_t*)&data.warning_overflow, sizeof(data.warning_overflow));

    // Data - slope_data[SLOPE_INDEX_MAX][4]
    file.write((uint8_t*)data.slope_data, sizeof(data.slope_data));

    // attit_data[3]
    file.write((uint8_t*)data.attit_data, sizeof(data.attit_data));

    // rocket_state[BOOL_DATA_LEN]
    file.write((uint8_t*)data.rocket_state, sizeof(data.rocket_state));

    // gps_data_d[DOUBLE_DATA_LEN]
    file.write((uint8_t*)data.gps_data_d, sizeof(data.gps_data_d));

    // local_gps_data_f[GPS_FLOAT_DATA_LEN]
    file.write((uint8_t*)data.local_gps_data_f, sizeof(data.local_gps_data_f));

    // LoRa
    file.write((uint8_t*)&data.last_recive_time, sizeof(data.last_recive_time));
    file.write((uint8_t*)&data.recive_pack_count, sizeof(data.recive_pack_count));

    // Warning (⚠ 不直接寫入 String 陣列 — 需轉成 C 字串或略過)
    // 建議只記錄 warning_index 個字串，或改為純 char[][] 儲存

    file.close();
    return true;
}
