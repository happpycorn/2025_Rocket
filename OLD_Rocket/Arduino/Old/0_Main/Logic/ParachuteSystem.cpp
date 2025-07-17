#include "ParachuteSystem.h"

void ParachuteSystem::decideDeployment(
    float altitude, float &o_slope, 
    bool *deployedState, bool &c1f, bool &c2f
) {
    float slope = calculateSlope(altitude);

    // 傘 1 開啟判斷
    if (!chuteDeployed[0]) {
        // 開傘條件 1 判斷
        if (isLaunchCondition(
            slope, altitude, 
            LAUNCH_1_LAUNCH_SLOPE, 
            LAUNCH_1_UPPER_BOUND, LAUNCH_1_BELOW_BOUND
        )) {
            // 開啟傘 1
            chuteDeployed[0] = true;
            lastDeployTime = xTaskGetTickCount();
        }
    // 傘 2 開啟判斷
    } else if (!chuteDeployed[1]) {
        // 傘 1 失效判斷
        if (isFailed(slope, LAUNCH_1_FAIL_SLOPE)) {
            // 開啟傘 2，並設為備用
            chuteDeployed[1] = true;
            D2_isSpare = true;
            chute1Failed = true;
            lastDeployTime = xTaskGetTickCount();
        // 開傘條件 2 判斷
        } else if (isLaunchCondition(
            slope, altitude, 
            LAUNCH_2_LAUNCH_SLOPE, 
            LAUNCH_2_UPPER_BOUND, LAUNCH_2_BELOW_BOUND
        )) {
            // 開啟傘 2
            chuteDeployed[1] = true;
            lastDeployTime = xTaskGetTickCount();
        }
    // 傘 3 開啟判斷
    } else if (!chuteDeployed[2]) {
        // 傘 2 備用判斷
        if (D2_isSpare) {
            // 傘 2 (備用)失效判斷
            if (isFailed(slope, LAUNCH_1_FAIL_SLOPE)) {
                // 開啟傘 3
                chuteDeployed[2] = true;
                chute2Failed = true;
            // 開傘條件 2 判斷
            } else if (isLaunchCondition(
                slope, altitude, 
                LAUNCH_2_LAUNCH_SLOPE, 
                LAUNCH_2_UPPER_BOUND, LAUNCH_2_BELOW_BOUND
            )) {
                // 開啟傘 3
                chuteDeployed[2] = true;
            }
        // 傘 2 失效判斷
        } else if (isFailed(slope, LAUNCH_2_FAIL_SLOPE)) {
            // 開啟傘 3
            chuteDeployed[2] = true;
            chute2Failed = true;
        }
    }

    o_slope = slope;

    for (int i = 0; i < 3; i++) {
        deployedState[i] = chuteDeployed[i];
    }

    c1f = chute1Failed;
    c2f = chute2Failed;
}

float ParachuteSystem::calculateSlope(float altitude) {

    alt_buffer[buffer_idx] = altitude;
    buffer_idx = (buffer_idx+1)%buffer_size;

    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    int start = buffer_idx;
    int end = buffer_size+buffer_idx;

    // 計算所需的和
    for (int i = start; i < end; ++i) {
        float x = i-buffer_idx;  // x 值是索引
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

bool ParachuteSystem::isLaunchCondition(
    float slope, float alt,  // 當前狀態
    float launch_slope,      // 參考斜率
    float alt_upper_bound, float alt_below_bound // 高度範圍
) {
    bool isSlopeValid = slope < launch_slope;
    bool isAltitudeValid = (alt_upper_bound > alt) && (alt > alt_below_bound);
    return isSlopeValid && isAltitudeValid;
}

bool ParachuteSystem::isFailed(float slope, float fail_slope) {
    long long afterChute = (xTaskGetTickCount() - lastDeployTime) * portTICK_PERIOD_MS;
    bool isChuteFailed = (afterChute > LAUNCH_TIME) && (slope < fail_slope);
    return isChuteFailed;
}
