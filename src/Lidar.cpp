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

int LIDAR::GetDistance() {
    return distance;
}

void LidarMeasurement() {
    for (int i = 0; i < LIDAR_NUM; i++) {
        lidar[i].distance = 0;
    }

    for (int i = LIDAR_MEA_MIN_ANG; i < LIDAR_MEA_MAX_ANG; i++) {
        for (int t = 0; t < LIDAR_NUM; t++) {
            lidar[t].servo.SetAngle(i);
        }

        for (int j = 0; j < LIDAR_MEA_TIME; j++) {
            for (int t = 0; t < LIDAR_NUM; t++) {
                vl53_sensors[t].UpdateDistance();

                // Serial.print(t);
                // Serial.print(" ");
                Serial.print(i);
                Serial.print(" ");
                Serial.print(vl53_sensors[t].GetDistance());
                Serial.print(" ");
                Serial.println(vl53_sensors[t].GetDistanceFiltered());
            }
        }
        Serial.println();
    }

    for (int i = LIDAR_MEA_MAX_ANG; i >= LIDAR_MEA_MIN_ANG; i--) {
        for (int t = 0; t < LIDAR_NUM; t++) {
            lidar[t].servo.SetAngle(i);
        }

        for (int j = 0; j < LIDAR_MEA_TIME; j++) {
            for (int t = 0; t < LIDAR_NUM; t++) {
                vl53_sensors[t].UpdateDistance();

                // Serial.print(t);
                // Serial.print(" ");
                Serial.print(i);
                Serial.print(" ");
                Serial.print(vl53_sensors[t].GetDistance());
                Serial.print(" ");
                Serial.println(vl53_sensors[t].GetDistanceFiltered());
            }
        }
        Serial.println();
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