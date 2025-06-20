#pragma once

#include "Constant.h"
#include <SPI.h>
#include <SD.h>

extern SPIClass mySPI;

class SDDataManager {
public:
    bool begin();
    bool saveData(const RecordData &data);
};
