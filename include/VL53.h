#ifndef _VL53_H_
#define _VL53_H_

#include <VL53L0X.h>

#include "Constant.h"
#include "KalmanFilter.h"

class VL53 {
   public:
    VL53();

    int distance;
    int distance_filtered;

    int distance_pre;
    int distance_filtered_pre;

    void UpdateDistance();

    friend bool VL53_INIT();

   private:
    VL53L0X sensor;
    KalmanFilter kf{2, 2, 0.02};
};

bool VL53_INIT();

extern VL53 vl53_sensors[LIDAR_NUM];

#endif