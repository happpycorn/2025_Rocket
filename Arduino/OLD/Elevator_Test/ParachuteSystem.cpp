#include "ParachuteSystem.h"

void ParachuteSystem::decideDeployment(
    float altitude, float slope, 
    bool &deployedState
) {
    if (!isLaunch) {
        bool isSlopeValid = slope < LAUNCH_SLOPE;
        bool isAltitudeValid = (LAUNCH_UPPER_BOUND > altitude) && (altitude > LAUNCH_BELOW_BOUND);
        if (isSlopeValid&&isAltitudeValid) {
            isLaunch = true;
        }
    }
    deployedState = isLaunch;
}

void ParachuteSystem::calculateSlope(unsigned long long time, float altitude, float &out_slope, float &out_sub_slope) {

    alt_buffer[buffer_idx] = altitude;
    time_buffer[buffer_idx] = time;
    if (valid_count <= buffer_size) {valid_count += 1;}

    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    int start = buffer_idx;
    int end = buffer_idx+valid_count;

    // 計算所需的和
    for (int i = start; i < end; ++i) {
        float x = time_buffer[i%buffer_size] / 1000.0f;
        float y_val = alt_buffer[i%buffer_size];

        sum_x += x;
        sum_y += y_val;
        sum_xy += x * y_val;
        sum_xx += x * x;
    }

    // 計算平均值
    float mean_x = sum_x / buffer_size;
    float mean_y = sum_y / buffer_size;

    // 計算斜率
    float slope = (sum_xy - buffer_size * mean_x * mean_y) / (sum_xx - buffer_size * mean_x * mean_x);

    slope_buffer[buffer_idx] = slope;

    sum_x = 0; sum_y = 0; sum_xy = 0; sum_xx = 0;

    // 計算所需的和
    for (int i = start; i < end; ++i) {
        float x = time_buffer[i%buffer_size] / 1000.0f;
        float y_val = slope_buffer[i%buffer_size];

        sum_x += x;
        sum_y += y_val;
        sum_xy += x * y_val;
        sum_xx += x * x;
    }

    // 計算平均值
    mean_x = sum_x / buffer_size;
    mean_y = sum_y / buffer_size;

    // 計算斜率
    float sub_slope = (sum_xy - buffer_size * mean_x * mean_y) / (sum_xx - buffer_size * mean_x * mean_x);

    buffer_idx = (buffer_idx+1)%buffer_size;

    out_slope = slope;
    out_sub_slope = sub_slope;
}
