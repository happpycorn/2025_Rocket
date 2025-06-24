#include "SDDataManager.h"

SPIClass mySPI(VSPI);

bool SDDataManager::begin() {
    mySPI.begin(21, 19, 18, SD_CS_PIN);

    if (!SD.begin(SD_CS_PIN, mySPI)) {  // 假設 SPI 接口的 CS 引腳是 5
        return false;
    }
    return true;
}

bool SDDataManager::saveData(const RecordData &data) {
    RecordData save_data;

    save_data.time = data.time;
    save_data.last_recive_time = data.last_recive_time;
    save_data.recive_pack_count = data.recive_pack_count;

    for (int i = 0; i < FLOAT_DATA_LEN; i++) save_data.f[i] = data.f[i];
    for (int i = 0; i < BOOL_DATA_LEN; i++) save_data.b[i] = data.b[i];
    for (int i = 0; i < DOUBLE_DATA_LEN; i++) save_data.d[i] = data.d[i];

    File file = SD.open("/reciveData.bin", FILE_APPEND);  // 打開二進制文件進行寫入

    if (!file) return false;

    file.write((uint8_t *)&save_data, sizeof(save_data));  // 直接將數據結構寫入文件
    file.close();  // 關閉文件
    return true;
}
