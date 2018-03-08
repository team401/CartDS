//
// Created by cameronearle on 2/26/18.
//

#include <iostream>
#include "LocalTriggers.hpp"
#include "LCD.hpp"


void LocalTriggers::onJoyHat(int hat, int value) {

}


void LocalTriggers::onJoyAxis(int axis, double value) {
    std::cout << "Axis: " << axis << "  Value: " << value;
    if (axis == 3) {
        double newValue = value * -1;
        newValue = newValue + 1;
        newValue = newValue / 2;
        LCD::setPower((int) newValue*100);
    }
}

void LocalTriggers::onJoyButton(int button, int value) {

}