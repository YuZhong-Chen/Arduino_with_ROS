#ifndef _CONSTANT_H_
#define _CONSTANT_H_

#define VL53_NUM 2
#define VL53_MEASUREMENT_MAX 1000

#define LIDAR_MEA_MAX_ANG 90
#define LIDAR_MEA_MIN_ANG 0
#define LIDAR_MEA_ANGLE_DIFF 2

#define LIDAR_STATE_IDLE 0
#define LIDAR_STATE_UP 1
#define LIDAR_STATE_DOWN 2

#define CAR_WIDTH 30.0
#define CAR_LENGTH 30.0
#define TRACK_WIDTH 100.0

#define FIRST_BUTTON_PIN 28
#define SECOND_BUTTON_PIN 30
#define THIRD_BUTTON_PIN 32

#define ENABLE_VL53
// #define ENABLE_FLOWSENSOR
// #define ENABLE_LIDAR
// #define ENABLE_BUTTON

extern const unsigned int LidarTable_1[];

#endif