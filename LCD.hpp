//
// Created by cameronearle on 4/17/17.
//

#ifndef CARTDS_OUTPUT_HPP
#define CARTDS_OUTPUT_HPP

#include <mutex>
#include <string>

class LCD {
public:
    static void init();
    static void setNowPlaying(std::string song);
    static void setVoltage(float volgate);
    static void setPower(int power);
    static void setMode(int mode);
private:
    static std::mutex lock;

    static int lcd;

    static void lcd_setup();
    static void lcd_setNowPlaying(std::string s);
    static void lcd_setVoltage(float v);
    static void lcd_setPower(int p);
    static void lcd_setMode(int m);
};


#endif //CARTDS_OUTPUT_HPP
