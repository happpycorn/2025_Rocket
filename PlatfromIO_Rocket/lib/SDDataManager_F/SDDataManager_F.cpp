#include "SDDataManager_F.h"

bool SDDataManager::begin() {
    if (!SD.begin(SD_CS_PIN)) return false;
    if (SD.exists("/data.csv")) return true;

    File file = SD.open("/data.csv", FILE_WRITE);
    if (!file) return false;

    // 寫入欄位名稱
    file.print("index,");

    for (int i = 0; i < LF_FLOAT_DATA_LEN; i++) {
        file.print(f_labels[i]); file.print(',');
    }

    for (int i = 0; i < LF_BOOL_DATA_LEN; i++) {
        file.print(b_labels[i]); file.print(',');
    }

    for (int i = 0; i < LF_DOUBLE_DATA_LEN; i++) {
        file.print(d_labels[i]);
        if (i < LF_DOUBLE_DATA_LEN - 1) file.print(',');
    }

    file.println();
    file.close();

    return true;
}

bool SDDataManager::saveData(const LFreqData &data) {
    File file = SD.open("/data.csv", FILE_APPEND);
    if (!file) return false;

    index += 1;
    file.print(index); file.print(',');

    for (int i = 0; i < LF_FLOAT_DATA_LEN; i++) {
        file.print(data.f[i], 6);  // 預設保留6位小數
        file.print(',');
    }

    for (int i = 0; i < LF_BOOL_DATA_LEN; i++) {
        file.print(data.b[i] ? 1 : 0);
        file.print(',');
    }

    for (int i = 0; i < LF_DOUBLE_DATA_LEN; i++) {
        file.print(data.d[i], 8);  // double可以保留更多位數
        if (i < LF_DOUBLE_DATA_LEN - 1) file.print(',');
    }

    file.println();  // 換行
    file.close();
    return true;
}
