#ifndef _SERVOCONTROL_H_
#define _SERVOCONTROL_H_

#include <Servo.h>

class ServoControl {
   public:
    ServoControl();

    // Initialize the Servo
    void Initialize(int ServoPin, bool isReverse);

    // Set the Angle and Run.
    void SetAngle(int Angle);

    // Set the Offset.
    void SetOffset(int offset);

   private:
    // The Object
    Servo servo;

    int num;

    // Servo offset -> Need to modify for every servo.
    int offset;

    // If the Servo's direction is wrong, set this to true.
    bool isReverse;

    double CurrentAngle;
};

#endif