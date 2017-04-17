//
// Created by cameronearle on 4/17/17.
//

#ifndef CARTDS_INPUT_HPP
#define CARTDS_INPUT_HPP


class Input {
public:
    static void init();
    static bool getEStop();
    static bool getEnabled();
    static bool getDisabled();
private:
    static int eStopPin;
    static int enabledPin;
    static int disabledPin;
};


#endif //CARTDS_INPUT_HPP
