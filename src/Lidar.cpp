#include "Lidar.h"

#include <Arduino.h>
#include <math.h>

static int num_count = 0;

LIDAR Lidar_Left;
// LIDAR Lidar_Right;

LIDAR::LIDAR() {
    num = num_count++;
}

void LIDAR::Initialize(int ServoPin, bool isReverse, int VL53_ID_Front, int VL53_ID_Back) {
    this->VL53_ID_Front = VL53_ID_Front;
    this->VL53_ID_Back = VL53_ID_Back;
    this->CurrentAngle = LIDAR_MEA_MIN_ANG;
    servo.Initialize(ServoPin, isReverse);
    servo.SetAngle(CurrentAngle);
    delay(200);
}

void LIDAR::SetState(int State) {
    this->State = State;

    if (State == LIDAR_STATE_UP) {
        max_Distance_diff_Front = max_Distance_diff_Back = 0;
        CharacteristicPoint_Front[0] = CharacteristicPoint_Front[1] = 0;
        CharacteristicPoint_Back[0] = CharacteristicPoint_Back[1] = 0;
    }
}

void LIDAR::Update() {
    switch (State) {
        case LIDAR_STATE_IDLE:
            break;

        case LIDAR_STATE_UP:
            if (CurrentAngle + LIDAR_MEA_ANGLE_DIFF > LIDAR_MEA_MAX_ANG) {
                State = LIDAR_STATE_DOWN;
            } else {
                CurrentAngle += LIDAR_MEA_ANGLE_DIFF;
                servo.SetAngle(CurrentAngle);

                vl53_sensors[VL53_ID_Front].UpdateDistance();
                vl53_sensors[VL53_ID_Back].UpdateDistance();
                Distance_diff_Front = abs(vl53_sensors[VL53_ID_Front].distance_filtered - vl53_sensors[VL53_ID_Front].distance_filtered_pre);
                Distance_diff_Back = abs(vl53_sensors[VL53_ID_Back].distance_filtered - vl53_sensors[VL53_ID_Back].distance_filtered_pre);

                if (Distance_diff_Front > max_Distance_diff_Front) {
                    max_Distance_diff_Front = Distance_diff_Front;
                    CharacteristicPoint_Front[0] = CurrentAngle;
                }
                if (Distance_diff_Back > max_Distance_diff_Back) {
                    max_Distance_diff_Back = Distance_diff_Back;
                    CharacteristicPoint_Back[0] = CurrentAngle;
                }
            }
            break;

        case LIDAR_STATE_DOWN:
            if (CurrentAngle - LIDAR_MEA_ANGLE_DIFF < LIDAR_MEA_MIN_ANG) {
                State = LIDAR_STATE_IDLE;
                // Push the predict answer here.
            } else {
                CurrentAngle -= LIDAR_MEA_ANGLE_DIFF;
                servo.SetAngle(CurrentAngle);

                vl53_sensors[VL53_ID_Front].UpdateDistance();
                vl53_sensors[VL53_ID_Back].UpdateDistance();
                Distance_diff_Front = abs(vl53_sensors[VL53_ID_Front].distance_filtered - vl53_sensors[VL53_ID_Front].distance_filtered_pre);
                Distance_diff_Back = abs(vl53_sensors[VL53_ID_Back].distance_filtered - vl53_sensors[VL53_ID_Back].distance_filtered_pre);

                if (Distance_diff_Front > max_Distance_diff_Front) {
                    max_Distance_diff_Front = Distance_diff_Front;
                    CharacteristicPoint_Front[1] = CurrentAngle;
                }
                if (Distance_diff_Back > max_Distance_diff_Back) {
                    max_Distance_diff_Back = Distance_diff_Back;
                    CharacteristicPoint_Back[1] = CurrentAngle;
                }
            }
            break;

        default:
            break;
    }
}

// TODO : Use all data to predict the average car info.
//        For now, I only use the front two lidars.
LIDAR_MEASUREMENT CalulateDistance(int mea_left1, int mea_left2, int mea_right1, int mea_right2) {
    LIDAR_MEASUREMENT an;

    an.Omega = acos(TRACK_WIDTH / (mea_left1 + mea_right1 + CAR_WIDTH));

    an.y = ((mea_right1 - mea_left1) * cos(an.Omega) + TRACK_WIDTH) / 2.0;

    if (mea_left1 >= mea_left2) {
        an.y += (CAR_LENGTH / 2) * sin(an.Omega);
        an.Omega = an.Omega * (180.0 / PI);
    } else {
        an.y -= (CAR_LENGTH / 2) * sin(an.Omega);
        an.Omega = (-1) * an.Omega * (180.0 / PI);
    }

    return an;
}

void LIDAR::SearchLidarTable() {
    if (num == 0) {
        Answer_Predict_Front = LidarTable_1[(CharacteristicPoint_Front[0] + CharacteristicPoint_Front[1]) / 2];
        Answer_Predict_Back = LidarTable_1[(CharacteristicPoint_Back[0] + CharacteristicPoint_Back[1]) / 2];
    }
}