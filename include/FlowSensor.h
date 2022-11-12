#ifndef _FLOWSENSOR_H_
#define _FLOWSENSOR_H_

#include "Bitcraze_PMW3901.h"
#include "KalmanFilter.h"
#include "ROS_node.h"

class FLOWSENSOR {
   public:
    FLOWSENSOR();
    void Initialize();

    void Reset();
    void UpdateData();

    void PublishData_Position();
    void PublishData_Velocity();

    // Unit : (??? / ms)
    double Velocity_X;
    double Velocity_Y;

    // Unit : (??? / ms)
    double Position_X;
    double Position_Y;

   private:
    // Using digital pin 10 for chip select
    Bitcraze_PMW3901 flow{10};

    KalmanFilter KalmanFilter_X{2, 2, 0.1};
    KalmanFilter KalmanFilter_Y{2, 2, 0.1};

    int16_t DeltaX;
    int16_t DeltaY;

    unsigned long LastTime;
    unsigned long CurrentTime;
    double DeltaTime;
};

extern FLOWSENSOR FlowSensor;

#endif