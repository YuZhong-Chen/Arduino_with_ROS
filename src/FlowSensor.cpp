#include "FlowSensor.h"

FLOWSENSOR FlowSensor;

static bool FirstUpdate;

FLOWSENSOR::FLOWSENSOR() {
    Reset();
}

void FLOWSENSOR::Initialize() {
    if (!flow.begin()) {
        Serial.println("Initialization of the flow sensor failed");
        while (1) {
        }
    }
}

void FLOWSENSOR::Reset() {
    Position_X = Position_Y = 0.0;
    FirstUpdate = true;
}

void FLOWSENSOR::UpdateData() {
    flow.readMotionCount(&(this->DeltaX), &(this->DeltaY));

    Velocity_X = KalmanFilter_X.updateEstimate(DeltaX);
    Velocity_Y = KalmanFilter_X.updateEstimate(DeltaY);

    // First measurement.
    if (FirstUpdate) {
        FirstUpdate = false;
        LastTime = micros();
        return;
    }

    // NOTE: 1,000,000 microseconds = 1 second
    CurrentTime = micros();
    DeltaTime = (double)(CurrentTime - LastTime) / 1000.0;

    Position_X += Velocity_X * DeltaTime;
    Position_Y += Velocity_Y * DeltaTime;

    LastTime = CurrentTime;
}

void FLOWSENSOR::PublishData_Position() {
    ROS_NODE::FlowSensor_Position_msg.x = Position_X;
    ROS_NODE::FlowSensor_Position_msg.y = Position_Y;

    ROS_NODE::Publish_FlowSensor_Pos();
}

void FLOWSENSOR::PublishData_Velocity() {
    ROS_NODE::FlowSensor_Velocity_msg.x = Velocity_X;
    ROS_NODE::FlowSensor_Velocity_msg.y = Velocity_Y;

    ROS_NODE::Publish_FlowSensor_Pos();
}