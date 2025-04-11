#ifndef PARACHUTE_SYSTEM_H
#define PARACHUTE_SYSTEM_H

#include <Arduino.h>

#define ALT_BUFFER_SIZE 100

#define LAUNCH_1_UPPER_BOUND 55
#define LAUNCH_1_BELOW_BOUND 50
#define LAUNCH_2_UPPER_BOUND 30
#define LAUNCH_2_BELOW_BOUND 20

#define LAUNCH_1_LAUNCH_SLOPE 0
#define LAUNCH_2_LAUNCH_SLOPE 0

#define LAUNCH_TIME 3000

#define LAUNCH_1_FAIL_SLOPE -2
#define LAUNCH_2_FAIL_SLOPE -2

class ParachuteSystem {
private:

    bool chuteDeployed[3] = {false, false, false};

    TickType_t lastDeployTime;

    bool chute1Failed = false;
    bool chute2Failed = false;

    bool D2_isSpare = false;

    float calculateSlope(float altitude);
    float alt_buffer[BUFFER_SIZE] = {0};
    int buffer_idx = 0;
    int buffer_size = BUFFER_SIZE;

    bool isLaunchCondition(
        float slope, float alt,  // 當前狀態
        float launch_slope,      // 參考斜率
        float alt_upper_bound, float alt_below_bound // 高度範圍
    );

    bool isFailed(float slope, float fail_slope);

public:

    void decideDeployment(
        float altitude, float &o_slope, 
        bool *deployedState, bool &c1f, bool &c2f
    );
};

#endif // PARACHUTE_SYSTEM_H