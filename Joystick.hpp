//
// Created by cameronearle on 4/16/17.
//

#ifndef CARTDS_JOYSTICK_HPP
#define CARTDS_JOYSTICK_HPP


#include <SDL2/SDL_events.h>

class Joystick {
public:
    static void initJoysticks();
    static void closeJoysticks();
    static void updateJoysticks();
private:
    const static int INVALID_ID;
    const static int SDL_AXIS_RANGE;
    static int initialized;
    static int joystickTracker;

    static int getId(int id);
    static void registerJoysticks();
    static void processHatEvent(SDL_Event* event);
    static void processAxisEvent(SDL_Event* event);
    static void processButtonEvent(SDL_Event* event);
};


#endif //CARTDS_JOYSTICK_HPP
