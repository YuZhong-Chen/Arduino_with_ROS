#include "Button.h"

#include <Arduino.h>

BUTTON Button[3];

BUTTON::BUTTON() {
    Init(2);
}

void BUTTON::Init(int Pin) {
    Status = false;
}

void BUTTON::UpdateStatus(int Pin) {
    Status = digitalRead(Pin);
}

void BUTTON::UpdateStatus() {
    Status = digitalRead(this->Pin);
}