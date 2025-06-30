#ifndef PARACHUTE_SYSTEM_H
#define PARACHUTE_SYSTEM_H

#include "Config.h"

class ParachuteSystem {
private:
    
    float alt_buffer[BUFFER_SIZE] = {0};
    float slope_buffer[BUFFER_SIZE] = {0};
    float time_buffer[BUFFER_SIZE] = {0};
    int buffer_idx = 0;
    int buffer_size = BUFFER_SIZE;
    bool isLaunch = false;

public:

    void fillSpace(unsigned long long time, float altitude);

    void calculateSlope(
        unsigned long long time, float altitude, 
        float &out_slope, float &out_sub_slope
    );

    void decideDeployment(
        float altitude, float slope, 
        bool &deployedState
    );
};

#endif // PARACHUTE_SYSTEM_H