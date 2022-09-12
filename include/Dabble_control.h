#ifndef _DABBLE_CONTROL_H_
#define _DABBLE_CONTROL_H_

// #define SHOW_DABBLEGAMEPAD_DATA

#define X_AXIS 0
#define Y_AXIS 1
#define Z_AXIS 2
#define GRIPPER_ANGLE 3

class DABBLE_GAMEPAD {
   public:
    DABBLE_GAMEPAD();

    void setup();
    void UpdateInput();

    // 0 -> X axis
    // 1 -> Y axis
    // 2 -> Z axis
    // 3 -> Gripper Angle
    float Data[4];

   private:
    int Z_AXIS_Width;
};

extern DABBLE_GAMEPAD DabbleGamePad;

#endif