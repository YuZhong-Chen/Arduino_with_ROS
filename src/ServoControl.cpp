#include "ServoControl.h"

static int num_count = 0;

ServoControl::ServoControl() {
    CurrentAngle = offset = 0;
    num = num_count++;
}

void ServoControl::Initialize(int ServoPin, bool isReverse) {
    servo.attach(ServoPin);
    this->isReverse = isReverse;
    servo.write(CurrentAngle);
}

// Set the Angle and Run.
void ServoControl::SetAngle(int Angle) {
    switch (num) {
        case 0:
            // servo.write(((Angle - offset) / 90.0) * 105.0);
            servo.write(Angle);
            break;
        case 1:
            // servo.write((((180 - Angle - 5)) / 90.0) * 85.0);
            servo.write(Angle);
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