#include "ROS_node.h"

ros::NodeHandle ROS_NodeHandle;

static float msg_vel[] = {0.0, 0.0, 0.0, 0.0};
static sensor_msgs::JointState msg;
static ros::Publisher EndEffectorVel_pub("RobotArmControl_Vel", &msg);

void ROS_NODE::setup() {
    ROS_NodeHandle.initNode();
    ROS_NodeHandle.advertise(EndEffectorVel_pub);

    msg.velocity_length = 4;
    msg.velocity = msg_vel;

    for (int i = 0; i < 4; i++) {
        msg.velocity[i] = 0.0;
    }
}

void ROS_NODE::Publish_RobotArmControl_Vel(float *velocity) {
    for (int i = 0; i < 4; i++) {
        msg.velocity[i] = velocity[i];
    }

    EndEffectorVel_pub.publish(&msg);
}

void ROS_NODE::SpinOnce() {
    ROS_NodeHandle.spinOnce();
}