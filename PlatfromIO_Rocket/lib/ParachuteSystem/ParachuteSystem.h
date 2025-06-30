#pragma once

#include "Constant.h"

class ParachuteSystem {
private:

    const int LAUNCH_1_UPPER_BOUND;
    const int LAUNCH_2_UPPER_BOUND;
    
    float time_buffer[PRC_BUFFER_SIZE] = {0};
    float alt_buffer[PRC_BUFFER_SIZE] = {0};
    float slope_buffer[PRC_BUFFER_SIZE] = {0};
    int buffer_idx = 0;
    int buffer_size = PRC_BUFFER_SIZE;

    bool chuteDeployed[3] = {false, false, false};
    bool isChute1Failed = false;
    bool isChute2Failed = false;

    unsigned long long lastDeployTime;
    float maxSubSlope = 0;

    bool isLaunchCondition(const float altitude, const float slope, const float upperBound);

    bool isFailed(const unsigned long long time, const float sub_slope);

    void calculateSlope(
        const unsigned long long time, const float altitude, float data[]
    );

public:

    ParachuteSystem(int L1UB, int L2UB) : LAUNCH_1_UPPER_BOUND(L1UB), LAUNCH_2_UPPER_BOUND(L2UB) {}

    void fillSpace(const unsigned long long time, const float altitude);

    float calculateAveAlt(const bool b1, const bool b2, const float a1, const float a2);

    void decideDeployment(
        const unsigned long long time,
        float array_f[], bool array_b[]
    );
};