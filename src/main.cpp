#include <Arduino.h>

#include "Dabble_control.h"
#include "ROS_node.h"

void setup() {
    Serial.begin(57600);
    DabbleGamePad.setup();
    ROS_NODE::setup();
}

void loop() {
    DabbleGamePad.UpdateInput();

    ROS_NODE::Publish_RobotArmControl_Vel(DabbleGamePad.Data);
    ROS_NODE::SpinOnce();
    delay(10);
}