#ifndef SDDataManager_h
#define SDDataManager_h

#include "0_Config.h"
#include <SPI.h>
#include <SD.h>

#define SD_CS_PIN 5

class SDDataManager {
public:
    bool begin();
    bool saveData(const TotalData &data);
};

#endif // SDDataManager_h
