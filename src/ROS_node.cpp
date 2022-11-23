#include "ROS_node.h"

ros::NodeHandle ROS_NodeHandle;

static float msg_vel[] = {0.0, 0.0, 0.0, 0.0};
static sensor_msgs::JointState RobotArmControl_Vel_msg;
static ros::Publisher EndEffectorVel_pub("RobotArmControl_Vel", &RobotArmControl_Vel_msg);

static int16_t msg_dis[] = {0, 0};
static std_msgs::Int16MultiArray CarDistanceFront_msg;
static ros::Publisher CarDistanceFront_pub("CarDistanceFront", &CarDistanceFront_msg);

geometry_msgs::Pose2D FlowSensor_Position_msg;
static ros::Publisher FlowSensor_Position_pub("/FlowSensor/Position", &FlowSensor_Position_msg);

geometry_msgs::Vector3 FlowSensor_Velocity_msg;
static ros::Publisher FlowSensor_Velocity_pub("/FlowSensor/Velocity", &FlowSensor_Velocity_msg);

static std_msgs::Int16 Button_msg;
static ros::Publisher Button_pub("/Button", &Button_msg);

void ROS_NODE::setup() {
    ROS_NodeHandle.initNode();

    ROS_NodeHandle.advertise(EndEffectorVel_pub);
    RobotArmControl_Vel_msg.velocity_length = 4;
    RobotArmControl_Vel_msg.velocity = msg_vel;
    for (int i = 0; i < 4; i++) {
        RobotArmControl_Vel_msg.velocity[i] = 0.0;
    }

    ROS_NodeHandle.advertise(CarDistanceFront_pub);
    CarDistanceFront_msg.data_length = 2;
    CarDistanceFront_msg.data = msg_dis;
    for (int i = 0; i < 2; i++) {
        CarDistanceFront_msg.data[i] = 0;
    }

    ROS_NodeHandle.advertise(FlowSensor_Position_pub);
    ROS_NodeHandle.advertise(FlowSensor_Velocity_pub);

    ROS_NodeHandle.advertise(Button_pub);
}

void ROS_NODE::Publish_RobotArmControl_Vel(float *Velocity) {
    for (int i = 0; i < 4; i++) {
        RobotArmControl_Vel_msg.velocity[i] = Velocity[i];
    }

    EndEffectorVel_pub.publish(&RobotArmControl_Vel_msg);
}

// Handle the data in RPI.
void ROS_NODE::Publish_CarDistanceFront(int *Distance) {
    for (int i = 0; i < 2; i++) {
        CarDistanceFront_msg.data[i] = Distance[i];
    }

    CarDistanceFront_pub.publish(&CarDistanceFront_msg);
}

void ROS_NODE::Publish_FlowSensor_Pos() {
    FlowSensor_Position_pub.publish(&FlowSensor_Position_msg);
}

void ROS_NODE::Publish_FlowSensor_Vel() {
    FlowSensor_Velocity_pub.publish(&FlowSensor_Velocity_msg);
}

void ROS_NODE::Publish_Button_State(int num) {
    Button_msg.data = num;
    Button_pub.publish(&Button_msg);
}

void ROS_NODE::SpinOnce() {
    ROS_NodeHandle.spinOnce();
}