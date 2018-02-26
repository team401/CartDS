#include <iostream>

#include "Log.hpp"
#include "lib/libds/include/LibDS.h"
#include "Input.hpp"
#include "LCD.hpp"
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "Joystick.hpp"
#include "lib/wiringpi/include/wiringPi.h"
#include "lib/libds/include/DS_Events.h"
#include "Music.hpp"

static bool running = true;
static int eStopCounter = 0;

void getUserInput() {
    if (Input::getEStop()) {
        eStopCounter++;
    } else {
        eStopCounter = 0;
    }

    if (eStopCounter > 10) {
        DS_SetEmergencyStopped(true);
        Log::w("UI", "Cart Estopped!  The RIO must be rebooted!");
    }

    if (Input::getEnabled()) {
        if (DS_GetCanBeEnabled()) {
            DS_SetControlMode(DS_CONTROL_TELEOPERATED);
            DS_SetRobotEnabled(true);
            Log::d("UI", "Cart Enabled");
        }
    }

    if (Input::getDisabled()) {
        DS_SetRobotEnabled(false);
        Log::d("UI", "Cart Disabled");
    }
}

void updateOutput() {
    if (DS_GetEmergencyStopped()) {
        LCD::setMode(3);
    } else {
        if (DS_GetRobotCommunications() && DS_GetRobotCode()) {
            LCD::setMode(DS_GetRobotEnabled());
        } else {
            LCD::setMode(2);
        }
    }
}

void processEvents() {
    DS_Event event;
    while (DS_PollEvent(&event)) {
        switch (event.type) {
            case DS_ROBOT_VOLTAGE_CHANGED:
                LCD::setVoltage(event.robot.voltage);
                break;
            case DS_ROBOT_ENABLED_CHANGED:
            case DS_ROBOT_ESTOP_CHANGED:
            case DS_ROBOT_COMMS_CHANGED:
            case DS_ROBOT_CODE_CHANGED:
                updateOutput();
                break;
        }
    }
}

int main() {
    Log::init(Log::Level::DEBUG, false); //Initialize the "logger", in this case more of an "output standard-izer"
    Log::setDoDebug(false); //Set the "output standard-izer" to show debugging messages

    wiringPiSetup(); //Set the pi inputs and outputs to use wiringpi pin numbering

    DS_Init(); //Start the driver station event loop

    DS_SetTeamNumber(401);
    DS_SetCustomRobotAddress("10.4.1.2"); //Set the robot address to the address of the 401 cRIO
    DS_Protocol ds2014 = DS_GetProtocolFRC_2014();
    DS_ConfigureProtocol(&ds2014); //Set the DS to use the 2014 protocol, which is the one for a cRIO
    DS_SetControlMode(DS_CONTROL_TELEOPERATED);

    Joystick::initJoysticks(); //Initialize the joysticks
    Input::init(); //Initialize the input buttons
    LCD::init(); //Initialize the LCD
    Music::init(); //Initialize the music player

    while (running) { //General DS task loop, runs forever (until system shutdown or 'q' is pressed)
        getUserInput(); //Read buttons on enclosure
        processEvents(); //Process any changes
        Joystick::updateJoysticks(); //Update the joysticks
        DS_Sleep(20);
    }

    DS_Close();
    Joystick::closeJoysticks();
    return EXIT_SUCCESS;
}