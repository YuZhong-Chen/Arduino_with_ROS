#include <Arduino.h>

// #include "Dabble_control.h"
#include "ROS_node.h"
#include "ServoControl.h"
#include "VL53.h"

ServoControl servo(false);

void setup() {
    Wire.begin();
    Serial.begin(57600);
    // DabbleGamePad.setup();
    ROS_NODE::setup();

    VL53_INIT();

    servo.Initialize(9);
}

void loop() {
    // DabbleGamePad.UpdateInput();

    // ROS_NODE::Publish_RobotArmControl_Vel(DabbleGamePad.Data);

    vl53_sensors[0].UpdateDistance();
    Serial.println(vl53_sensors[0].GetDistanceFiltered());

    ROS_NODE::SpinOnce();
    delay(10);
}