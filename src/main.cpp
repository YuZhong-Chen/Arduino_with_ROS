#include <Arduino.h>

// #include "Dabble_control.h"
#include "Lidar.h"
#include "ROS_node.h"

void setup() {
    Wire.begin();
    Serial.begin(57600);

    // DabbleGamePad.setup();
    ROS_NODE::setup();

    VL53_INIT();

    lidar[0].Initialize(9);

    delay(400);
}

void loop() {
    // DabbleGamePad.UpdateInput();

    LidarMeasurement();

    // ROS_NODE::Publish_RobotArmControl_Vel(DabbleGamePad.Data);
    // ROS_NODE::SpinOnce();
    // delay(10);
}