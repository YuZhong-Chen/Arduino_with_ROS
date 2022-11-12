#ifndef _LIDAR_H_
#define _LIDAR_H_

#include "Constant.h"
#include "ServoControl.h"
#include "VL53.h"

class LIDAR {
   public:
    LIDAR();
    void Initialize(int ServoPin, bool isReverse, int VL53_ID_Front, int VL53_ID_Back);

    ServoControl servo;
    int Distance_Front;
    int Distance_diff_Front;

    int Distance_Back;
    int Distance_diff_Back;

    int CharacteristicPoint_Front[2];
    int CharacteristicPoint_Back[2];

    int Answer_Predict_Front;
    int Answer_Predict_Back;
    void SearchLidarTable();
    void SetState(int State);

    void Update();

   private:
    int num;

    int VL53_ID_Front;
    int VL53_ID_Back;

    int CurrentAngle;

    int max_Distance_diff_Front;
    int max_Distance_diff_Back;

    int State;
};

typedef struct {
    double y = 0;
    double Omega = 0;
} LIDAR_MEASUREMENT;

LIDAR_MEASUREMENT CalulateDistance(int mea_left1, int mea_left2, int mea_right1, int mea_right2);

extern LIDAR Lidar_Left;
// extern LIDAR Lidar_Right;

#endif