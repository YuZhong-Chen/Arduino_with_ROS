#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Dabble.h>
#include <ros.h>

#include "sensor_msgs/JointState.h"

ros::NodeHandle nh;

float vel[] = {0.0, 0.0, 0.0, 0.0};
sensor_msgs::JointState msg;
ros::Publisher EndEffectorVel_pub("RobotArmControl_Vel", &msg);

float X_axis = 0, Y_axis = 0, Z_axis = 0;
int Z_size = 1;
int GripperAngle = 90;

void setup() {
    nh.initNode();
    nh.advertise(EndEffectorVel_pub);

    msg.velocity_length = 4;
    msg.velocity = vel;

    for (int i = 0; i < 4; i++) {
        msg.velocity[i] = 0.0;
    }

    Serial.begin(57600);
    Dabble.begin(9600);
}

void loop() {
    Dabble.processInput();  // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

    Z_axis = 0;
    if (GamePad.isStartPressed()) {
        if (Z_size >= 2) {
            Z_size -= 1;
        }
    }
    if (GamePad.isSelectPressed()) {
        if (Z_size <= 6) {
            Z_size += 1;
        }
    }
    if (GamePad.isTrianglePressed()) {
        Z_axis = Z_size;
    }
    if (GamePad.isCrossPressed()) {
        Z_axis = -Z_size;
    }
    if (GamePad.isCirclePressed()) {
        GripperAngle = 75;
    }
    if (GamePad.isSquarePressed()) {
        GripperAngle = 110;
    }

    X_axis = GamePad.getXaxisData();
    Y_axis = GamePad.getYaxisData();
    Serial.print("x_axis: ");
    Serial.print(X_axis);
    Serial.print("\ty_axis: ");
    Serial.print(Y_axis);
    Serial.print("\tz_axis: ");
    Serial.println(Z_axis);

    msg.velocity[0] = X_axis;
    msg.velocity[1] = Y_axis;
    msg.velocity[2] = Z_axis;
    msg.velocity[3] = GripperAngle;
    EndEffectorVel_pub.publish(&msg);

    nh.spinOnce();
    delay(10);
}