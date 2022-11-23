#ifndef _ROS_NODE_H_
#define _ROS_NODE_H_

#include <ros.h>

#include "geometry_msgs/Pose2D.h"
#include "geometry_msgs/Vector3.h"
#include "sensor_msgs/JointState.h"
#include "std_msgs/Int16.h"
#include "std_msgs/Int16MultiArray.h"

namespace ROS_NODE {
void setup();
void Publish_RobotArmControl_Vel(float *Velocity);
void Publish_CarDistanceFront(int *Distance);
void Publish_FlowSensor_Vel();
void Publish_FlowSensor_Pos();
void Publish_FlowSensor_Pos();
void Publish_Button_State(int num);
void SpinOnce();
}  // namespace ROS_NODE

extern geometry_msgs::Pose2D FlowSensor_Position_msg;
extern geometry_msgs::Vector3 FlowSensor_Velocity_msg;

#endif