//
// Created by cameronearle on 2/26/18.
//

#ifndef CARTDS_LOCALTRIGGERS_HPP
#define CARTDS_LOCALTRIGGERS_HPP


class LocalTriggers {
public:
    static void onJoyHat(int hat, int value);
    static void onJoyAxis(int axis, double value);
    static void onJoyButton(int button, int value);
};


#endif //CARTDS_LOCALTRIGGERS_HPP
