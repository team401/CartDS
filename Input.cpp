//
// Created by cameronearle on 4/17/17.
//

#include "Input.hpp"
#include "lib/wiringpi/include/wiringPi.h"

int Input::eStopPin = 0;
int Input::disabledPin = 2;
int Input::enabledPin = 3;

void Input::init() {
    pinMode(eStopPin, INPUT);
    pinMode(disabledPin, INPUT);
    pinMode(enabledPin, INPUT);
    pullUpDnControl(eStopPin, PUD_DOWN);
    pullUpDnControl(disabledPin, PUD_DOWN);
    pullUpDnControl(enabledPin, PUD_DOWN);
}

bool Input::getEStop() {
    return digitalRead(eStopPin);
}

bool Input::getDisabled() {
    return digitalRead(disabledPin);
}

bool Input::getEnabled() {
    return digitalRead(enabledPin);
}