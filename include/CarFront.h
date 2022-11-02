#ifndef _CARFRONT_H_
#define _CARFRONT_H_

#include "VL53.h"

class CARFRONT {
   public:
    CARFRONT();

    void Initialize(int ID_right, int ID_left);

    void UpdateDistance();
    void PublishData();

   private:
    // Use to Publish Data to RPI.
    int Distance[2];

    // VL53 ID (In order to access the VL53)
    int VL53_ID_right;
    int VL53_ID_left;
};

extern CARFRONT CarFrontSensor;

#endif