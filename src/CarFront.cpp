#include "CarFront.h"

#include "ROS_node.h"

CARFRONT CarFrontSensor;

CARFRONT::CARFRONT() {
    // FrontDetect VL53 ID
    Initialize(0, 1);
}

void CARFRONT::Initialize(int ID_right, int ID_left) {
    VL53_ID_right = ID_right;
    VL53_ID_left = ID_left;
}

// Update the VL53.
// (It may cost some time !!! )
void CARFRONT::UpdateDistance() {
    vl53_sensors[VL53_ID_right].UpdateDistance();
    vl53_sensors[VL53_ID_left].UpdateDistance();
}

// Publish the data to RPI.
void CARFRONT::PublishData() {
    Distance[0] = vl53_sensors[VL53_ID_left].distance_filtered;
    Distance[1] = vl53_sensors[VL53_ID_right].distance_filtered;
    ROS_NODE::Publish_CarDistanceFront(Distance);
}