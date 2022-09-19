#include "VL53.h"

#include <math.h>

VL53 vl53_sensors[VL53_NUM];

VL53::VL53() {
}

void VL53::UpdateDistance() {
    distance = (int)sensor.readRangeContinuousMillimeters();
    if (distance > MEASUREMENT_MAX) {
        distance = MEASUREMENT_MAX;
    }
    distance_filtered = (int)kf.updateEstimate((double)distance);
}

int VL53::GetDistance() {
    return distance;
}

int VL53::GetDistanceFiltered() {
    return distance_filtered;
}

void VL53_INIT() {
    for (int i = 0; i < VL53_NUM; i++) {
        pinMode(VL53_SHUTDOWN_PIN_START + i, OUTPUT);
        digitalWrite(VL53_SHUTDOWN_PIN_START + i, LOW);
    }
    delay(500);

    for (int i = 0; i < VL53_NUM; i++) {
        digitalWrite(VL53_SHUTDOWN_PIN_START + i, HIGH);
        delay(150);
        vl53_sensors[i].sensor.init(true);
        delay(100);
        vl53_sensors[i].sensor.setAddress((uint8_t)(i + 1));
    }

    for (int i = 0; i < VL53_NUM; i++) {
        vl53_sensors[i].sensor.startContinuous();
    }
}