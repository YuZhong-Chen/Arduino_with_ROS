#ifndef _VL53_H_
#define _VL53_H_

#include <VL53L0X.h>

#include "KalmanFilter.h"

#define VL53_NUM 1
#define VL53_SHUTDOWN_PIN_START 5
#define MEASUREMENT_MAX 1000

class VL53 {
   public:
    VL53();

    void UpdateDistance();
    int GetDistance();
    int GetDistanceFiltered();

    friend void VL53_INIT();

   private:
    VL53L0X sensor;
    KalmanFilter kf{2, 2, 0.02};
    int distance;
    int distance_filtered;
};

void VL53_INIT();

extern VL53 vl53_sensors[VL53_NUM];

#endif