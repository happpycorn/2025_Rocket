#ifndef PARACHUTE_SYSTEM_H
#define PARACHUTE_SYSTEM_H

#include "Config.h"

class ParachuteSystem {
private:
    
    float alt_buffer[PRC_BUFFER_SIZE] = {0};
    float slope_buffer[PRC_BUFFER_SIZE] = {0};
    float time_buffer[PRC_BUFFER_SIZE] = {0};
    int buffer_idx = 0;
    int buffer_size = PRC_BUFFER_SIZE;

    bool chuteDeployed[3] = {false, false, false};
    bool isChute1Failed = false;
    bool isChute2Failed = false;

    TickType_t lastDeployTime;
    const TickType_t deployDelayTicks = pdMS_TO_TICKS(DEPLOY_DELAY);
    float maxSubSlope = 0;

public:

    void fillSpace(unsigned long long time, float altitude);

    float calculateAveAlt(bool b1, bool b2, float a1, float a2);

    void calculateSlope(
        unsigned long long time, float altitude, float data[]
    );

    void decideDeployment(
        float altitude, float slope, float sub_slope,
        bool deployedState[]
    );

    bool isLaunchCondition(float altitude, float slope, float upperBound);

    bool isFailed(float sub_slope);
};

#endif // PARACHUTE_SYSTEM_H