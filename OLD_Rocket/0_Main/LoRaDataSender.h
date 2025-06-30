#ifndef LoRaDataSender_h
#define LoRaDataSender_h

#include <SPI.h>
#include <LoRa.h>
#include "0_Config.h"

#define NSS     5       // CS 引腳
#define RESET   4       // RESET 引腳
#define DIO0    15      // DIO0 引腳
#define FREQ    433E6   // 频率

class LoRaDataSender {
public:

    bool begin();
    void sendTotalData(TotalData &data);

private:

    void serializeTotalData(TotalData &data, byte *buffer);
};

#endif // LoRaDataSender_h
