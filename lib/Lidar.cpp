#include "Lidar.h"

#include <Arduino.h>

static int num_count = 0;

LIDAR lidar[LIDAR_NUM];

LIDAR::LIDAR() {
    num = num_count++;
}

void LIDAR::Initialize(int ServoPin) {
    servo.Initialize(ServoPin);
    servo.SetAngle(LIDAR_MEA_MIN_ANG);
    delay(200);
    for (int j = 0; j < 10; j++) {
        vl53_sensors[num].UpdateDistance();
    }
}

void LidarMeasurement() {
    for (int i = 0; i < LIDAR_NUM; i++) {
        lidar[i].Distance = 0;
    }

    for (int i = 0; i < LIDAR_NUM; i++) {
        lidar[i].max_Distance_diff = 0;
        // lidar[i].CharacteristicPoint[0] = lidar[i].CharacteristicPoint[1] = 0;
    }

    for (int angle = LIDAR_MEA_MIN_ANG; angle < LIDAR_MEA_MAX_ANG; angle += LIDAR_MEA_ANGLE_DIFF) {
        for (int num = 0; num < LIDAR_NUM; num++) {
            lidar[num].servo.SetAngle(angle);
        }

        for (int j = 0; j < LIDAR_MEA_TIME; j++) {
            for (int num = 0; num < LIDAR_NUM; num++) {
                vl53_sensors[num].UpdateDistance();

                lidar[num].Distance_diff = abs(vl53_sensors[num].GetDistanceFiltered() - vl53_sensors[num].GetDistanceFilteredPre());

                if (lidar[num].Distance_diff > lidar[num].max_Distance_diff) {
                    lidar[num].max_Distance_diff = lidar[num].Distance_diff;
                    lidar[num].CharacteristicPoint[0] = angle;
                }

                // Serial.print(t);
                // Serial.print(" ");
                // Serial.print(angle);
                // Serial.print(" ");
                // Serial.print(vl53_sensors[num].GetDistance());
                // Serial.print(" ");
                // Serial.print(vl53_sensors[num].GetDistanceFiltered());
                // Serial.print(" ");
                // Serial.print(lidar[num].Distance_diff);

                // Serial.print(" ");
                // Serial.print(lidar[num].CharacteristicPoint[0]);
                // Serial.print(" ");
                // Serial.println(lidar[num].CharacteristicPoint[1]);
            }
        }
        // Serial.println();
    }

    for (int i = 0; i < LIDAR_NUM; i++) {
        lidar[i].max_Distance_diff = 0;
    }

    for (int angle = LIDAR_MEA_MAX_ANG; angle >= LIDAR_MEA_MIN_ANG; angle -= LIDAR_MEA_ANGLE_DIFF) {
        for (int num = 0; num < LIDAR_NUM; num++) {
            lidar[num].servo.SetAngle(angle);
        }

        for (int j = 0; j < LIDAR_MEA_TIME; j++) {
            for (int num = 0; num < LIDAR_NUM; num++) {
                vl53_sensors[num].UpdateDistance();

                lidar[num].Distance_diff = abs(vl53_sensors[num].GetDistanceFiltered() - vl53_sensors[num].GetDistanceFilteredPre());

                if (lidar[num].Distance_diff > lidar[num].max_Distance_diff) {
                    lidar[num].max_Distance_diff = lidar[num].Distance_diff;
                    lidar[num].CharacteristicPoint[1] = angle;
                }

                // Serial.print(t);
                // Serial.print(" ");
                // Serial.print(angle);
                // Serial.print(" ");
                // Serial.print(vl53_sensors[num].GetDistance());
                // Serial.print(" ");
                // Serial.print(vl53_sensors[num].GetDistanceFiltered());
                // Serial.print(" ");
                // Serial.print(lidar[num].Distance_diff);

                // Serial.print(" ");
                // Serial.print(lidar[num].CharacteristicPoint[0]);
                // Serial.print(" ");
                // Serial.println(lidar[num].CharacteristicPoint[1]);
            }
        }
        // Serial.println();
    }

    Serial.print(lidar[0].CharacteristicPoint[0]);
    Serial.print(" ");
    Serial.print(lidar[0].CharacteristicPoint[1]);
    Serial.print(" ");
    Serial.println((lidar[0].CharacteristicPoint[0] + lidar[0].CharacteristicPoint[1]) / 2);
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
        Answer_Predict = LidarTable_1[(CharacteristicPoint[0] + CharacteristicPoint[1]) / 2];
    }
}