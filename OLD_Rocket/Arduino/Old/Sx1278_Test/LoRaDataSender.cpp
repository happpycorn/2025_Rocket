#include "LoRaDataSender.h"

void LoRaDataSender::begin() {
    loraSerial.begin(baudRate, SERIAL_8N1, rx, tx);
}

void LoRaDataSender::sendTotalData(const TotalData &data) {
    byte buffer[512];
    size_t length = 0;
    serializeTotalData(data, buffer, length);
    sendBufferAsHex(buffer, length);
}

void LoRaDataSender::serializeTotalData(const TotalData &data, byte *buffer, size_t &len) {
    int index = 0;
    auto copy = [&](auto field) {
        memcpy(&buffer[index], &field, sizeof(field));
        index += sizeof(field);
    };

    copy(data.temperature);
    copy(data.pressure);
    copy(data.altitude);
    copy(data.humidity);

    for (int i = 0; i < 3; i++) {
        copy(data.accels[i]);
        copy(data.gyros[i]);
        copy(data.mags[i]);
    }

    copy(data.aSqrt);
    copy(data.mDirection);
    copy(data.slope);

    for (int i = 0; i < 3; i++) copy(data.servos_state[i]);
    copy(data.chute1Failed);
    copy(data.chute2Failed);

    for (int i = 0; i < 2; i++) copy(data.sensor_state.barometer[i]);
    copy(data.sensor_state.accel);
    copy(data.sensor_state.hygro);
    copy(data.isHaveSensor);

    copy(data.gps_data.latitude);
    copy(data.gps_data.longitude);
    copy(data.gps_data.altitude);
    copy(data.gps_data.geoidSeparation);
    copy(data.gps_data.utcTime);
    copy(data.gps_data.groundSpeed);
    copy(data.gps_data.heading);
    copy(data.gps_data.verticalSpeed);
    copy(data.gps_data.numSatellites);
    copy(data.gps_data.numVisibleSat);
    copy(data.gps_data.hdop);
    copy(data.gps_data.pdop);
    copy(data.gps_data.signalQuality);
    copy(data.gps_data.fixType);
    copy(data.gps_data.gnssSystem);
    copy(data.gps_data.accEst);
    copy(data.gps_data.accVel);

    len = index;
}

void LoRaDataSender::sendBufferAsHex(byte* buffer, size_t len) {
    loraSerial.print("S:");
    for (size_t i = 0; i < len; i++) {
        if (buffer[i] < 16) loraSerial.print("0");
        loraSerial.print(buffer[i], HEX);
    }
    loraSerial.println();
}
