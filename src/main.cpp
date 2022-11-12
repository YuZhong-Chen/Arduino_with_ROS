#include <Arduino.h>

#include "CarFront.h"
#include "FlowSensor.h"
#include "Lidar.h"
#include "ROS_node.h"

LIDAR_MEASUREMENT Car_Info;

void setup() {
    Wire.begin();
    Serial.begin(57600);

    // Init the ros node
    ROS_NODE::setup();

    // Init the VL53 sensor.
    VL53::Initialize();

    // TODO Remember to modify the pin. //46
    Lidar_Left.Initialize(45, false, 0, 1);

    // Init the FlowSensor.
    FlowSensor.Initialize();

    delay(400);
}

void loop() {
    /* Get the FrontDistance. */
    CarFrontSensor.UpdateDistance();
    CarFrontSensor.PublishData();

    // for (int i = 0; i < VL53_NUM; i++) {
    //     vl53_sensors[i].UpdateDistance();
    //     Serial.print(vl53_sensors[i].distance);
    //     Serial.print(" ");
    // }
    // Serial.println("");

    FlowSensor.UpdateData();
    FlowSensor.PublishData_Position();
    FlowSensor.PublishData_Velocity();

    ROS_NODE::SpinOnce();
    // delay(10);
}