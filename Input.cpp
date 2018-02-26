//
// Created by cameronearle on 4/17/17.
//

#include "Input.hpp"
#include "Constants.hpp"
#include "lib/wiringpi/include/wiringPi.h"

void Input::init() {
    pinMode(ESTOP_PIN, INPUT);
    pinMode(DISABLED_PIN, INPUT);
    pinMode(ENABLED_PIN, INPUT);
    pullUpDnControl(ESTOP_PIN, PUD_DOWN);
    pullUpDnControl(DISABLED_PIN, PUD_DOWN);
    pullUpDnControl(ENABLED_PIN, PUD_DOWN);
}

bool Input::getEStop() {
    return digitalRead(ESTOP_PIN);
}

bool Input::getDisabled() {
    return digitalRead(DISABLED_PIN);
}

bool Input::getEnabled() {
    return digitalRead(ENABLED_PIN);
}