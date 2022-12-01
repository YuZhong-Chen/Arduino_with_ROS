#include "Button.h"

#include <Arduino.h>

#include "Constant.h"

BUTTON Button[3];

const int ButtonPin[3] = {FIRST_BUTTON_PIN, SECOND_BUTTON_PIN, THIRD_BUTTON_PIN};

BUTTON::BUTTON() {
}

void BUTTON::Init(int num) {
    CurrentStatus = PreviousStatus = false;
    this->Pin = ButtonPin[num];
}

void BUTTON::UpdateStatus(int Pin) {
    PreviousStatus = CurrentStatus;
    CurrentStatus = digitalRead(Pin);
}

void BUTTON::UpdateStatus() {
    PreviousStatus = CurrentStatus;
    CurrentStatus = digitalRead(this->Pin);
}

bool BUTTON::isEnable() {
    return (PreviousStatus != CurrentStatus && CurrentStatus == HIGH);
}