#ifndef PARACHUTE_SYSTEM_H
#define PARACHUTE_SYSTEM_H

#define ALT_BUFFER_SIZE 100

class ParachuteSystem {
private:
    
    float alt_buffer[ALT_BUFFER_SIZE] = {0};
    float time_buffer[ALT_BUFFER_SIZE] = {0};
    int buffer_idx = 0;
    int buffer_size = ALT_BUFFER_SIZE;

public:

    float calculateSlope(unsigned long long time, float altitude);
};

#endif // PARACHUTE_SYSTEM_H