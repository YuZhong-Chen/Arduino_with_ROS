#include "FlowSensor.h"

FLOWSENSOR FlowSensor;

FLOWSENSOR::FLOWSENSOR() {
    Reset();
    IgnoreFirstNData = 10;
}

void FLOWSENSOR::Initialize() {
    if (!flow.begin()) {
        Serial.println("Fail to Init FlowSensor.");
        while (1) {
        }
    }
}

void FLOWSENSOR::Reset() {
    Position_X = Position_Y = 0.0;
    FirstNData = 0;
}

void FLOWSENSOR::UpdateData() {
    flow.readMotionCount(&(this->DeltaX), &(this->DeltaY));

    // First measurement.
    if (FirstNData < IgnoreFirstNData) {
        FirstNData += 1;
        LastTime = millis();
        return;
    }

    Velocity_X = KalmanFilter_X.updateEstimate(DeltaX);
    Velocity_Y = KalmanFilter_Y.updateEstimate(DeltaY);

    // Velocity_X = (double)DeltaX;
    // Velocity_Y = (double)DeltaY;

    // NOTE: 1,000,000 microseconds = 1 second
    // 1000 ms = 1 second
    CurrentTime = millis();
    DeltaTime = (double)(CurrentTime - LastTime) / 1000.0;

    Position_X += Velocity_X * DeltaTime;
    Position_Y += Velocity_Y * DeltaTime;

    LastTime = CurrentTime;
}

void FLOWSENSOR::PublishData_Position() {
    FlowSensor_Position_msg.x = Position_X;
    FlowSensor_Position_msg.y = Position_Y;

    ROS_NODE::Publish_FlowSensor_Pos();
}

void FLOWSENSOR::PublishData_Velocity() {
    FlowSensor_Velocity_msg.x = Velocity_X;
    FlowSensor_Velocity_msg.y = Velocity_Y;

    ROS_NODE::Publish_FlowSensor_Vel();
}