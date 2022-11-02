#include <Arduino.h>

#include "Lidar.h"
#include "ROS_node.h"

LIDAR_MEASUREMENT Car_Info;

void setup() {
    Wire.begin();
    Serial.begin(57600);
    delay(400);

    // Init the ros node
    ROS_NODE::setup();

    // Init the VL53 sensors, it will hang at here if fail to init sensors.
    if (!VL53_INIT()) {
        Serial.println("Fail to Init VL53 sensors.");
        while (1) {
        }
    }

    // lidar[0].Initialize(9);

    delay(400);
}

void loop() {
    // LidarMeasurement();

    for (int i = 0; i < LIDAR_NUM; i++) {
        vl53_sensors[i].UpdateDistance();
        Serial.print(vl53_sensors[i].GetDistance());
        Serial.print(" ");
    }
    Serial.println("");

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