#ifndef PARACHUTE_SYSTEM_H
#define PARACHUTE_SYSTEM_H

#define ALT_BUFFER_SIZE 100

#define LAUNCH_UPPER_BOUND 55
#define LAUNCH_BELOW_BOUND 50

#define LAUNCH_SLOPE -0.5

class ParachuteSystem {
private:
    
    float alt_buffer[BUFFER_SIZE] = {0};
    float slope_buffer[BUFFER_SIZE] = {0};
    float time_buffer[BUFFER_SIZE] = {0};
    int buffer_idx = 0;
    int buffer_size = BUFFER_SIZE;
    int valid_count = 0;
    bool isLaunch = false;

public:

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