#include <iostream>

#include "Log.hpp"
#include "lib/libds/include/LibDS.h"
#include <pthread.h>
#include <termios.h>
#include <unistd.h>
#include <cstdlib>
#include "Joystick.hpp"
#include "lib/wiringpi/include/wiringPi.h"

static bool running = true;

char getch() {
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
}

void* getUserInput(void*) {
    while (running) {
        if (getch() == 'q') {
            running = 0; //Tell the program to stop
        }
        DS_Sleep(20);
    }
    pthread_exit(0);
    return NULL;
}

void processEvents() {

}

int main() {
    Log::init(Log::Level::DEBUG, false); //Initialize the "logger", in this case more of an "output standard-izer"
    Log::setDoDebug(true); //Set the "output standard-izer" to show debugging messages

    DS_Init(); //Start the driver station event loop
    DS_SetCustomRobotAddress("10.4.1.2"); //Set the robot address to the address of the 401 cRIO
    DS_ConfigureProtocol(DS_GetProtocolFRC_2014()); //Set the DS to use the 2014 protocol, which is the one for a cRIO

    Joystick::initJoysticks(); //Initialize the joysticks

    pthread_t userInputThread;
    pthread_create(&userInputThread, NULL, &getUserInput, NULL);

    while (running) { //General DS task loop, runs forever (until system shutdown or 'q' is pressed
        processEvents(); //Process any changes
        Joystick::updateJoysticks(); //Update the joysticks
        DS_Sleep(20);
    }

    DS_Close();
    Joystick::closeJoysticks();
    return EXIT_SUCCESS;
}