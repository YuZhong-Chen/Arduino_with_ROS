#ifndef _ROS_NODE_H_
#define _ROS_NODE_H_

#include <ros.h>

#include "sensor_msgs/JointState.h"

namespace ROS_NODE {
void setup();
void Publish_RobotArmControl_Vel(float *velocity);
void SpinOnce();
}  // namespace ROS_NODE

#endif