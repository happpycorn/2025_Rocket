#include "ParachuteSystem.h"

void ParachuteSystem::fillSpace(const unsigned long long time, const float altitude) {
    alt_buffer[buffer_idx] = altitude;
    time_buffer[buffer_idx] = time;
    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    int start = buffer_idx;
    int end = buffer_idx+buffer_size;

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

    buffer_idx = (buffer_idx+1)%buffer_size;
}

void ParachuteSystem::decideDeployment(
    const unsigned long long time,
    float array_f[], bool array_b[]
) {
    calculateSlope(time, array_f[SLOPE_DATA_ADDR+0], array_f);

    const float altitude = array_f[SLOPE_DATA_ADDR+0];
    const float slope = array_f[SLOPE_DATA_ADDR+1];
    const float sub_slope = array_f[SLOPE_DATA_ADDR+2];

    // 傘 1 開啟判斷
    if (!chuteDeployed[0]) {
        // 開傘條件 1 判斷
        if (isLaunchCondition(altitude, slope, LAUNCH_1_UPPER_BOUND)) {
            // 開啟傘 1
            chuteDeployed[0] = true;
            lastDeployTime = time;
            maxSubSlope = 0;
        }
    // 傘 2 開啟判斷
    } else if (!chuteDeployed[1]) {
        // 傘 1 失效判斷
        if (isFailed(time, sub_slope)) {
            // 開啟傘 2，並設為備用
            chuteDeployed[1] = true;
            isChute1Failed = true;
            lastDeployTime = time;
            maxSubSlope = 0;
        // 開傘條件 2 判斷
        } else if (isLaunchCondition(altitude, slope, LAUNCH_2_UPPER_BOUND)) {
            // 開啟傘 2
            chuteDeployed[1] = true;
            lastDeployTime = time;
            maxSubSlope = 0;
        }
    // 傘 3 開啟判斷
    } else if (!chuteDeployed[2]) {
        // 傘 2 備用判斷
        if (isChute1Failed) {
            // 傘 2 (備用)失效判斷
            if (isFailed(time, sub_slope)) {
                // 開啟傘 3
                chuteDeployed[2] = true;
                isChute2Failed = true;
            // 開傘條件 2 判斷
            } else if (isLaunchCondition(altitude, slope, LAUNCH_2_UPPER_BOUND)) {
                // 開啟傘 3
                chuteDeployed[2] = true;
            }
        // 傘 2 失效判斷
        } else if (isFailed(time, sub_slope)) {
            // 開啟傘 3
            chuteDeployed[2] = true;
            isChute2Failed = true;
        }
    }

    for (int i = 0; i < 3; i++) {
        array_b[i] = chuteDeployed[i];
    }

    array_b[3] = isChute1Failed;
    array_b[4] = isChute2Failed;
}

void ParachuteSystem::calculateSlope(
    const unsigned long long time, const float altitude, float data[]
) {

    alt_buffer[buffer_idx] = altitude;
    time_buffer[buffer_idx] = time;

    float sum_x = 0, sum_y = 0, sum_xy = 0, sum_xx = 0;

    int start = buffer_idx;
    int end = buffer_idx+buffer_size;

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

    data[SLOPE_DATA_ADDR+1] = slope;
    data[SLOPE_DATA_ADDR+2] = sub_slope;
}

float ParachuteSystem::calculateAveAlt(bool b1, bool b2, float a1, float a2) {
    int validCount = b1 + b2;
    return validCount ? (a1*b1+a2*b2)/validCount : NAN;
}

bool ParachuteSystem::isLaunchCondition(float altitude, float slope, float upperBound) {
    bool isSlopeValid = slope < LAUNCH_SLOPE;
    bool isAltitudeValid = (upperBound > altitude) && (altitude > LAUNCH_BELOW_BOUND);
    return isSlopeValid && isAltitudeValid;
}

bool ParachuteSystem::isFailed(const unsigned long long time, const float sub_slope) {
    maxSubSlope = (sub_slope > maxSubSlope) ? sub_slope : maxSubSlope;

    unsigned long long elapsedTime = time - lastDeployTime;
    if (elapsedTime < DEPLOY_DELAY) {
        return false;
    } else if (maxSubSlope > UNFAIL_SUB_SLOPE) {
        return false;
    } else {
        return true;
    }
}