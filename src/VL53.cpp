#include "VL53.h"

#include <math.h>

VL53 vl53_sensors[VL53_NUM];

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

// Init the VL53 sensors, it will hang at here if fail to init sensors.
void VL53::Initialize() {
    bool isSuccess = true;

    // TODO  Remember to modify the pin.
    // (According to the Physic connection.)
    int Shutdown_Pin[6] = {38, 39, 7, 8, 9, 10};

    // Shutdown the sensor.
    for (int i = 0; i < VL53_NUM; i++) {
        pinMode(Shutdown_Pin[i], OUTPUT);
        digitalWrite(Shutdown_Pin[i], LOW);
    }
    delay(500);

    // Naming.
    for (int i = 0; i < VL53_NUM; i++) {
        digitalWrite(Shutdown_Pin[i], HIGH);
        delay(150);
        if (!vl53_sensors[i].sensor.init(true)) {
            isSuccess = false;
            break;
        }
        delay(100);
        vl53_sensors[i].sensor.setAddress((uint8_t)(i + 1));
    }

    if (!isSuccess) {
        Serial.println("Fail to Init VL53 sensors.");
        // while (1) {
        // }
        return;
    }

    for (int i = 0; i < VL53_NUM; i++) {
        vl53_sensors[i].sensor.startContinuous();
    }

    // Belows code can be deleted if you want.
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < VL53_NUM; j++) {
            vl53_sensors[j].UpdateDistance();
        }
    }
}