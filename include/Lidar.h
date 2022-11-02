#ifndef _LIDAR_H_
#define _LIDAR_H_

#include "Constant.h"
#include "ServoControl.h"
#include "VL53.h"

class LIDAR {
   public:
    LIDAR();
    void Initialize(int ServoPin);

    ServoControl servo{false};
    int Distance;
    int Distance_diff;

    int CharacteristicPoint[2];

    int Answer_Predict;
    void SearchLidarTable();

    friend void LidarMeasurement();

   private:
    int num;
    int max_Distance_diff;
};

typedef struct {
    double y = 0;
    double Omega = 0;
} LIDAR_MEASUREMENT;

void LidarMeasurement();
LIDAR_MEASUREMENT CalulateDistance(int mea_left1, int mea_left2, int mea_right1, int mea_right2);

extern LIDAR lidar[LIDAR_NUM];

#endif