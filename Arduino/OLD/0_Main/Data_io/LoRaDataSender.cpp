#include "LoRaDataSender.h"

bool LoRaDataSender::begin() {
    if (!LoRa.begin(FREQ)) {
        return false;
    }
    LoRa.setPins(NSS, RESET, DIO0);
    return true;
}

// 發送數據
void LoRaDataSender::sendTotalData(TotalData &data) {
    byte buffer[512];  // 根據數據大小調整緩衝區
    serializeTotalData(data, buffer);

    LoRa.beginPacket();
    LoRa.write(buffer, sizeof(buffer));  // 發送整個字節流
    LoRa.endPacket();
}

// 序列化 TotalData 為字節流
void LoRaDataSender::serializeTotalData(TotalData &data, byte *buffer) {
    int index = 0;

    // 序列化 SensorData
    memcpy(&buffer[index], &data.temperature, sizeof(data.temperature));
    index += sizeof(data.temperature);  
    memcpy(&buffer[index], &data.pressure, sizeof(data.pressure));
    index += sizeof(data.pressure);
    memcpy(&buffer[index], &data.altitude, sizeof(data.altitude));
    index += sizeof(data.altitude);
    memcpy(&buffer[index], &data.humidity, sizeof(data.humidity));
    index += sizeof(data.humidity);

    // 依次序列化 accels, gyros, mags, aSqrt, mDirection, slope
    for (int i = 0; i < 3; i++) {
        memcpy(&buffer[index], &data.accels[i], sizeof(data.accels[i]));
        index += sizeof(data.accels[i]);
        memcpy(&buffer[index], &data.gyros[i], sizeof(data.gyros[i]));
        index += sizeof(data.gyros[i]);
        memcpy(&buffer[index], &data.mags[i], sizeof(data.mags[i]));
        index += sizeof(data.mags[i]);
    }

    memcpy(&buffer[index], &data.aSqrt, sizeof(data.aSqrt));
    index += sizeof(data.aSqrt);
    memcpy(&buffer[index], &data.mDirection, sizeof(data.mDirection));
    index += sizeof(data.mDirection);
    memcpy(&buffer[index], &data.slope, sizeof(data.slope));
    index += sizeof(data.slope);

    // 序列化 servos_state, chute1Failed, chute2Failed, sensor_state
    for (int i = 0; i < 3; i++) {
        memcpy(&buffer[index], &data.servos_state[i], sizeof(data.servos_state[i]));
        index += sizeof(data.servos_state[i]);
    }
    memcpy(&buffer[index], &data.chute1Failed, sizeof(data.chute1Failed));
    index += sizeof(data.chute1Failed);
    memcpy(&buffer[index], &data.chute2Failed, sizeof(data.chute2Failed));
    index += sizeof(data.chute2Failed);

    // 序列化 SensorState
    for (int i = 0; i < 2; i++) {
        memcpy(&buffer[index], &data.sensor_state.barometer[i], sizeof(data.sensor_state.barometer[i]));
        index += sizeof(data.sensor_state.barometer[i]);
    }
    memcpy(&buffer[index], &data.sensor_state.accel, sizeof(data.sensor_state.accel));
    index += sizeof(data.sensor_state.accel);
    memcpy(&buffer[index], &data.sensor_state.hygro, sizeof(data.sensor_state.hygro));
    index += sizeof(data.sensor_state.hygro);

    // 序列化 isHaveSensor
    memcpy(&buffer[index], &data.isHaveSensor, sizeof(data.isHaveSensor));
    index += sizeof(data.isHaveSensor);

    // 序列化 GPSData
    memcpy(&buffer[index], &data.gps_data.latitude, sizeof(data.gps_data.latitude));
    index += sizeof(data.gps_data.latitude);
    memcpy(&buffer[index], &data.gps_data.longitude, sizeof(data.gps_data.longitude));
    index += sizeof(data.gps_data.longitude);
    memcpy(&buffer[index], &data.gps_data.altitude, sizeof(data.gps_data.altitude));
    index += sizeof(data.gps_data.altitude);
    memcpy(&buffer[index], &data.gps_data.geoidSeparation, sizeof(data.gps_data.geoidSeparation));
    index += sizeof(data.gps_data.geoidSeparation);
    memcpy(&buffer[index], &data.gps_data.utcTime, sizeof(data.gps_data.utcTime));
    index += sizeof(data.gps_data.utcTime);
    memcpy(&buffer[index], &data.gps_data.groundSpeed, sizeof(data.gps_data.groundSpeed));
    index += sizeof(data.gps_data.groundSpeed);
    memcpy(&buffer[index], &data.gps_data.heading, sizeof(data.gps_data.heading));
    index += sizeof(data.gps_data.heading);
    memcpy(&buffer[index], &data.gps_data.verticalSpeed, sizeof(data.gps_data.verticalSpeed));
    index += sizeof(data.gps_data.verticalSpeed);
    memcpy(&buffer[index], &data.gps_data.numSatellites, sizeof(data.gps_data.numSatellites));
    index += sizeof(data.gps_data.numSatellites);
    memcpy(&buffer[index], &data.gps_data.numVisibleSat, sizeof(data.gps_data.numVisibleSat));
    index += sizeof(data.gps_data.numVisibleSat);
    memcpy(&buffer[index], &data.gps_data.hdop, sizeof(data.gps_data.hdop));
    index += sizeof(data.gps_data.hdop);
    memcpy(&buffer[index], &data.gps_data.pdop, sizeof(data.gps_data.pdop));
    index += sizeof(data.gps_data.pdop);
    memcpy(&buffer[index], &data.gps_data.signalQuality, sizeof(data.gps_data.signalQuality));
    index += sizeof(data.gps_data.signalQuality);
    memcpy(&buffer[index], &data.gps_data.fixType, sizeof(data.gps_data.fixType));
    index += sizeof(data.gps_data.fixType);
    memcpy(&buffer[index], &data.gps_data.gnssSystem, sizeof(data.gps_data.gnssSystem));
    index += sizeof(data.gps_data.gnssSystem);
    memcpy(&buffer[index], &data.gps_data.accEst, sizeof(data.gps_data.accEst));
    index += sizeof(data.gps_data.accEst);
    memcpy(&buffer[index], &data.gps_data.accVel, sizeof(data.gps_data.accVel));
}