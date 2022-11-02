#include "VL53.h"

#include <math.h>

VL53 vl53_sensors[VL53_num];

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

bool VL53_INIT() {
    // TODO  Remember to modify the pin.
    // (According to the Physic connection.)
    int Shutdown_Pin[6] = {5, 6, 7, 8, 9, 10};

    for (int i = 0; i < VL53_num; i++) {
        pinMode(Shutdown_Pin[i], OUTPUT);
        digitalWrite(Shutdown_Pin[i], LOW);
    }
    delay(500);

    for (int i = 0; i < VL53_num; i++) {
        digitalWrite(Shutdown_Pin[i], HIGH);
        delay(150);
        if (!vl53_sensors[i].sensor.init(true)) {
            return false;
        }
        delay(100);
        vl53_sensors[i].sensor.setAddress((uint8_t)(i + 1));
    }

    for (int i = 0; i < VL53_num; i++) {
        vl53_sensors[i].sensor.startContinuous();
    }

    return true;
}