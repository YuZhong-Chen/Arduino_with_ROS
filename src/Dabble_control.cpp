#include "Dabble_control.h"

// This is used to setting Dabble GamePad. Don't modify it !!!
#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#include <Arduino.h>
#include <Dabble.h>

DABBLE_GAMEPAD DabbleGamePad;

DABBLE_GAMEPAD::DABBLE_GAMEPAD() {
    for (int i = 0; i < 3; i++) {
        Data[i] = 0;
    }
    Data[GRIPPER_ANGLE] = 90;

    Z_AXIS_Width = 7;
}

void DABBLE_GAMEPAD::setup() {
    Dabble.begin(9600);
}

void DABBLE_GAMEPAD::UpdateInput() {
    Dabble.processInput();  // this function is used to refresh data obtained from smartphone.Hence calling this function is mandatory in order to get data properly from your mobile.

    Data[X_AXIS] = GamePad.getXaxisData();
    Data[Y_AXIS] = GamePad.getYaxisData();

    // For Z Axis
    if (GamePad.isStartPressed()) {
        if (Z_AXIS_Width >= 2) {
            Z_AXIS_Width -= 1;
        }
    }
    if (GamePad.isSelectPressed()) {
        if (Z_AXIS_Width <= 6) {
            Z_AXIS_Width += 1;
        }
    }
    if (GamePad.isTrianglePressed()) {
        Data[Z_AXIS] = Z_AXIS_Width;
    } else if (GamePad.isCrossPressed()) {
        Data[Z_AXIS] = -Z_AXIS_Width;
    } else {
        Data[Z_AXIS] = 0;
    }

    // For Gripper Angle
    if (GamePad.isCirclePressed()) {
        Data[GRIPPER_ANGLE] = 75;
    }
    if (GamePad.isSquarePressed()) {
        Data[GRIPPER_ANGLE] = 110;
    }

#ifdef SHOW_DABBLEGAMEPAD_DATA
    Serial.print("x_axis: ");
    Serial.print(Axis[X_AXIS]);
    Serial.print("\ty_axis: ");
    Serial.print(Axis[Y_AXIS]);
    Serial.print("\tz_axis: ");
    Serial.println(Axis[Z_AXIS]);
#endif
}