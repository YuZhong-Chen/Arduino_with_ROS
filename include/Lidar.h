#ifndef _LIDAR_H_
#define _LIDAR_H_

#include "Constant.h"
#include "ServoControl.h"
#include "VL53.h"

class LIDAR {
   public:
    LIDAR();
    void Initialize(int ServoPin);

    friend void LidarMeasurement();

   private:
    int num;

    ServoControl servo{false};

    int distance;
};

void LidarMeasurement();

extern LIDAR lidar[LIDAR_NUM];

#endif