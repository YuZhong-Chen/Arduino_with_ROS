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

/**
 *  ID  Use
 *  0   Front left   (Lidar)
 *  1   Back left    (lidar)
 *  2   Front right  (lidar)
 *  3   Back right   (lidar)
 *  4   Front left   (FrontDetect)
 *  5   Front right  (FrontDetect)
 */
extern VL53 vl53_sensors[VL53_num];

#endif