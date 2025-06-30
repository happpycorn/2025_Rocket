#include "SDDataManager_F.h"

bool SDDataManager::begin() {
    if (!SD.begin(SD_CS_PIN)) {  // 假設 SPI 接口的 CS 引腳是 5
        return false;
    }
    return true;
}

bool SDDataManager::saveData(const LFreqData &data) {

    LFreqData save_data;

    for (int i = 0; i < LF_FLOAT_DATA_LEN; i++) {save_data.f[i] = data.f[i];}

    for (int i = 0; i < LF_BOOL_DATA_LEN; i++) {save_data.b[i] = data.b[i];}

    for (int i = 0; i < LF_DOUBLE_DATA_LEN; i++) {save_data.d[i] = data.d[i];}

    File file = SD.open("/data.bin", FILE_APPEND);  // 打開二進制文件進行寫入

    if (!file) {
        return false;
    }

    file.write((uint8_t *)&save_data, sizeof(save_data));  // 直接將數據結構寫入文件
    file.close();  // 關閉文件
    return true;
}
