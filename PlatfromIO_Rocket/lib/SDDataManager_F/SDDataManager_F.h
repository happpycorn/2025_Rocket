#pragma once

#include "Constant.h"
#include <SPI.h>
#include <SD.h>

class SDDataManager {
public:
    bool begin();
    bool saveData(const LFreqData &data);
};
