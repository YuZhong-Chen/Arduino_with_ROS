#include "VL53.h"

#include <math.h>

VL53 vl53_sensors[LIDAR_NUM];

VL53::VL53() {
    distance = distance_filtered = distance_pre = distance_filtered_pre = 0;
}

void VL53::UpdateDistance() {
    distance_pre = distance;
    distance_filtered_pre = distance_filtered;

    distance = (int)sensor.readRangeContinuousMillimeters();
    if (distance > VL53_MEASUREMENT_MAX) {
        distance = VL53_MEASUREMENT_MAX;
    }
    distance_filtered = (int)kf.updateEstimate((double)distance);
}

int VL53::GetDistance() {
    return distance;
}

int VL53::GetDistanceFiltered() {
    return distance_filtered;
}

int VL53::GetDistancePre() {
    return distance_pre;
}
int VL53::GetDistanceFilteredPre() {
    return distance_filtered_pre;
}

void VL53_INIT() {
    for (int i = 0; i < LIDAR_NUM; i++) {
        pinMode(VL53_SHUTDOWN_PIN_START + i, OUTPUT);
        digitalWrite(VL53_SHUTDOWN_PIN_START + i, LOW);
    }
    delay(500);

    for (int i = 0; i < LIDAR_NUM; i++) {
        digitalWrite(VL53_SHUTDOWN_PIN_START + i, HIGH);
        delay(150);
        vl53_sensors[i].sensor.init(true);
        delay(100);
        vl53_sensors[i].sensor.setAddress((uint8_t)(i + 1));
    }

    for (int i = 0; i < LIDAR_NUM; i++) {
        vl53_sensors[i].sensor.startContinuous();
    }
}