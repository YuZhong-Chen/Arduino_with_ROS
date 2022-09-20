#include <Arduino.h>

// #include "Dabble_control.h"
#include "Lidar.h"
#include "ROS_node.h"

LIDAR_MEASUREMENT Car_Info;

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

    // Car_Info = CalulateDistance(lidar[0].GetDistance(), lidar[1].GetDistance(), lidar[2].GetDistance(), 0);
    // Serial.println("Car Info (lidar calculate) : ");
    // Serial.print("Omega : ");
    // Serial.println(Car_Info.Omega);
    // Serial.print("Y : ");
    // Serial.println(Car_Info.y);

    // ROS_NODE::Publish_RobotArmControl_Vel(DabbleGamePad.Data);
    // ROS_NODE::SpinOnce();
    // delay(10);
}