#include "ParachuteSystem.h"

float ParachuteSystem::calculateSlope(unsigned long long time, float altitude) {

    alt_buffer[buffer_idx] = altitude;
    time_buffer[buffer_idx] = time;
    buffer_idx = (buffer_idx+1)%buffer_size;

    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    int start = buffer_idx;
    int end = buffer_size+buffer_idx;

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
    return slope;
}
