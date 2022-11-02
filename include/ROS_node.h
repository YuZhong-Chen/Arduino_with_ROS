#ifndef _ROS_NODE_H_
#define _ROS_NODE_H_

#include <ros.h>

#include "sensor_msgs/JointState.h"
#include "std_msgs/Int16MultiArray.h"

namespace ROS_NODE {
void setup();
void Publish_RobotArmControl_Vel(float *velocity);
void Publish_CarDistanceFront(int *Distance);
void SpinOnce();
}  // namespace ROS_NODE

#endif