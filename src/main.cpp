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

#ifdef ENABLE_LIDAR
    // TODO Remember to modify the pin. //46
    Lidar_Left.Initialize(45, false, 0, 1);
#endif

#ifdef ENABLE_FLOWSENSOR
    // Init the FlowSensor.
    FlowSensor.Initialize();
#endif

    if (usb.Init() == -1) {
        Serial.println("Fail to Init USB shield.");
        while (true) {
        }
    }
    Serial.begin(57600);

    delay(400);

#ifdef ENABLE_BUTTON

    // Init Button PinMode.
    pinMode(FIRST_BUTTON_PIN, INPUT);
    pinMode(SECOND_BUTTON_PIN, INPUT);
    pinMode(THIRD_BUTTON_PIN, INPUT);

    delay(500);

    Button[0].UpdateStatus(FIRST_BUTTON_PIN);
    Button[1].UpdateStatus(SECOND_BUTTON_PIN);
    Button[2].UpdateStatus(THIRD_BUTTON_PIN);

    if (Button[0].Status == HIGH) {
        ROS_NODE::Publish_Button_State(0);
    } else if (Button[1].Status == HIGH) {
        ROS_NODE::Publish_Button_State(1);
    } else if (Button[2].Status == HIGH) {
        ROS_NODE::Publish_Button_State(2);
    }

    // Serial.print(Button[0].Status);
    // Serial.print(" ");
    // Serial.print(Button[1].Status);
    // Serial.print(" ");
    // Serial.println(Button[2].Status);
#endif
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

    // FlowSensor.UpdateData();

    // Serial.print("x ");
    // Serial.print(FlowSensor.Velocity_X);
    // Serial.print(" ");
    // Serial.println(FlowSensor.Velocity_Y);
    // Serial.print(" ");
    // Serial.print(FlowSensor.Position_X);
    // Serial.print(" ");
    // Serial.println(FlowSensor.Position_Y);

    // FlowSensor.PublishData_Position();
    // FlowSensor.PublishData_Velocity();

    ROS_NODE::SpinOnce();
    delay(50);
}