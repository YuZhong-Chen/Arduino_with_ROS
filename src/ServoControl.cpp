#include "ServoControl.h"

static int num_count = 0;

ServoControl::ServoControl(bool isReverse) {
    this->isReverse = isReverse;
    CurrentAngle = offset = 0;
    num = num_count++;
}

void ServoControl::Initialize(int ServoPin) {
    servo.attach(ServoPin);
    servo.write(CurrentAngle);
}

// Set the Angle and Run.
void ServoControl::SetAngle(int Angle) {
    switch (num) {
        case 0:
            servo.write(((Angle - offset) / 90.0) * 105.0);
            break;
        case 1:
            // servo.write(((Angle - offset) / 90.0) * 105.0);
            break;
        case 2:
            // servo.write(((Angle - offset) / 90.0) * 105.0);
            break;

        default:
            break;
    }

    CurrentAngle = Angle;
}

// Set the Offset.
void ServoControl::SetOffset(int offset) {
    this->offset = offset;
}