#include <Arduino.h>

#include "Button.h"
#include "CarFront.h"
#include "Constant.h"
#include "FlowSensor.h"
#include "Lidar.h"
#include "ROS_node.h"
#include "Usb.h"

LIDAR_MEASUREMENT Car_Info;

USB usb;

void setup() {
    Wire.begin();

    // Init the ros node
    ROS_NODE::setup();

#ifdef ENABLE_VL53
    // Init the VL53 sensor.
    VL53::Initialize();
#endif

#ifdef ENABLE_BUTTON
    // Init Button PinMode.
    pinMode(FIRST_BUTTON_PIN, INPUT);
    pinMode(SECOND_BUTTON_PIN, INPUT);
    pinMode(THIRD_BUTTON_PIN, INPUT);

    for (int i = 0; i < 3; i++) {
        Button[i].Init(i);
    }
#endif

#ifdef ENABLE_FLOWSENSOR
    // Init the FlowSensor.
    FlowSensor.Initialize();
#endif

    if (usb.Init() == -1) {
        Serial.println("Fail to Init USB shield.");
        // while (true) {
        // }
    }

    Serial.begin(57600);
    delay(500);
}

void loop() {
#ifdef ENABLE_VL53
    /* Get the FrontDistance. */
    CarFrontSensor.UpdateDistance();
    CarFrontSensor.PublishData();

    // for (int i = 0; i < VL53_NUM; i++) {
    //     vl53_sensors[i].UpdateDistance();
    //     Serial.print(vl53_sensors[i].distance);
    //     Serial.print(" ");
    // }
    // Serial.println("");
#endif

#ifdef ENABLE_BUTTON
    for (int i = 0; i < 3; i++) {
        Button[i].UpdateStatus();
        if (Button[i].isEnable()) {
            ROS_NODE::Publish_Button_State(i + 1);
        }
    }
#endif

    ROS_NODE::SpinOnce();
    delay(50);
}