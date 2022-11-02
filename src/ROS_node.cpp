#include "ROS_node.h"

ros::NodeHandle ROS_NodeHandle;

static float msg_vel[] = {0.0, 0.0, 0.0, 0.0};
static sensor_msgs::JointState RobotArmControl_Vel_msg;
static ros::Publisher EndEffectorVel_pub("RobotArmControl_Vel", &RobotArmControl_Vel_msg);

static int16_t msg_dis[] = {0, 0};
static std_msgs::Int16MultiArray CarDistanceFront_msg;
static ros::Publisher CarDistanceFront_pub("CarDistanceFront", &CarDistanceFront_msg);

void ROS_NODE::setup() {
    ROS_NodeHandle.initNode();
    ROS_NodeHandle.advertise(EndEffectorVel_pub);

    RobotArmControl_Vel_msg.velocity_length = 4;
    RobotArmControl_Vel_msg.velocity = msg_vel;

    CarDistanceFront_msg.data_length = 2;
    CarDistanceFront_msg.data = msg_dis;

    for (int i = 0; i < 4; i++) {
        RobotArmControl_Vel_msg.velocity[i] = 0.0;
    }
    for (int i = 0; i < 2; i++) {
        CarDistanceFront_msg.data[i] = 0;
    }
}

void ROS_NODE::Publish_RobotArmControl_Vel(float *velocity) {
    for (int i = 0; i < 4; i++) {
        RobotArmControl_Vel_msg.velocity[i] = velocity[i];
    }

    EndEffectorVel_pub.publish(&RobotArmControl_Vel_msg);
}

void ROS_NODE::Publish_CarDistanceFront(int *Distance) {
    for (int i = 0; i < 2; i++) {
        CarDistanceFront_msg.data[i] = Distance[i];
    }

    CarDistanceFront_pub.publish(&CarDistanceFront_msg);
}

void ROS_NODE::SpinOnce() {
    ROS_NodeHandle.spinOnce();
}