#include "SDDataManager.h"

bool SDDataManager::begin() {
    if (!SD.begin(SD_CS_PIN)) {  // 假設 SPI 接口的 CS 引腳是 5
        return false;
    }
    return true;
}

bool SDDataManager::saveData(const LFreqData &data) {
    File file = SD.open("/data.bin", FILE_APPEND);  // 打開二進制文件進行寫入

    if (!file) {
        return false;
    }

    file.write((uint8_t *)&data, sizeof(data));  // 直接將數據結構寫入文件
    file.close();  // 關閉文件
    return true;
}
