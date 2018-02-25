//
// Created by cameronearle on 4/16/17.
//

#include "Joystick.hpp"
#include "Log.hpp"

#include <SDL2/SDL.h>
#include "lib/libds/include/LibDS.h"
#include "Output.hpp"
#include <stdio.h>
#include <pthread.h>

const int Joystick::INVALID_ID = -1;
const int Joystick::SDL_AXIS_RANGE = 0x8000;
int Joystick::initialized = 0;
int Joystick::joystickTracker = -1;

int Joystick::getId(int id) {
    int joystick = id;
    joystick = abs(joystickTracker - (joystick + 1));

    if (joystick >= SDL_NumJoysticks()) {
        joystick -= 1;
    }

    return joystick;
}

void Joystick::registerJoysticks() {
    DS_JoysticksReset();

    int i;
    for (i = 0; i < SDL_NumJoysticks(); ++i) {
        SDL_Joystick* joystick = SDL_JoystickOpen(i);

        if (joystick) {
            DS_JoysticksAdd (SDL_JoystickNumAxes(joystick),
                             SDL_JoystickNumHats(joystick),
                             SDL_JoystickNumButtons(joystick));
        }
    }
}

void Joystick::processHatEvent(SDL_Event *event) {
    if (!event) {
        return;
    }

    int angle = 0;
    int hat = event->jhat.hat;
    int joystick = getId(event->jhat.which);

    switch (event->jhat.value) {
        case SDL_HAT_RIGHTUP:
            angle = 45;
            break;
        case SDL_HAT_RIGHTDOWN:
            angle = 135;
            break;
        case SDL_HAT_LEFTDOWN:
            angle = 225;
            break;
        case SDL_HAT_LEFTUP:
            angle = 315;
            break;
        case SDL_HAT_UP:
            angle = 0;
            break;
        case SDL_HAT_RIGHT:
            angle = 90;
            break;
        case SDL_HAT_DOWN:
            angle = 180;
            break;
        case SDL_HAT_LEFT:
            angle = 270;
            break;
        default:
            angle = -1;
            break;
    }

    if (joystick > INVALID_ID) {
        DS_SetJoystickHat(joystick, hat, angle);
    }
}

void Joystick::processAxisEvent(SDL_Event *event) {
    if (!event) {
        return;
    }

    int axis = event->jaxis.axis;
    int joystick = getId(event->jaxis.which);
    double value = ((double) (event->jaxis.value)) / SDL_AXIS_RANGE;

    if (axis == 3) {
        double newValue = value * -1;
        newValue = newValue + 1;
        newValue = newValue / 2;
        Output::setPower((int) newValue*100);
    }

    if (joystick > INVALID_ID) {
        DS_SetJoystickAxis(joystick, axis, value);
    }
}

void Joystick::processButtonEvent(SDL_Event *event) {
    if (!event) {
        return;
    }

    int button = event->jbutton.button;
    int joystick = getId(event->jbutton.which);
    int pressed = (event->jbutton.state == SDL_PRESSED);

    if (joystick > INVALID_ID) {
        DS_SetJoystickButton(joystick, button, pressed);
    }
}

void Joystick::initJoysticks() {
    if (SDL_Init(SDL_INIT_JOYSTICK) == 0) {
        initialized = 1;
        SDL_JoystickEventState(SDL_ENABLE);
    } else {
        Log::e("Joystick", "Cannot initialize SDL!");
        exit(1);
    }
}

void Joystick::closeJoysticks() {
    int i;
    for (i = 0; i < SDL_NumJoysticks(); ++i) {
        SDL_JoystickClose(SDL_JoystickOpen(i));
    }
    SDL_Quit();
}

void Joystick::updateJoysticks() {
    if (!initialized) {
        return;
    }

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_JOYDEVICEADDED:
                ++joystickTracker;
                registerJoysticks();
                break;
            case SDL_JOYDEVICEREMOVED:
                registerJoysticks();
                break;
            case SDL_JOYAXISMOTION:
                processAxisEvent(&event);
                break;
            case SDL_JOYHATMOTION:
                processHatEvent(&event);
                break;
            case SDL_JOYBUTTONDOWN:
                processButtonEvent(&event);
                break;
            case SDL_JOYBUTTONUP:
                processButtonEvent(&event);
                break;
            default:
                break;
        }
    }
}