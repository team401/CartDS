//
// Created by cameronearle on 4/17/17.
//

#include "Output.hpp"
#include <mutex>
#include "lib/wiringpi/include/wiringPi.h"
#include "lib/wiringpi/include/lcd.h"

std::mutex Output::lock;

int Output::lcd = -1;

const int Output::LCD_RS = 25;
const int Output::LCD_E = 24;
const int Output::LCD_D4  = 23;
const int Output::LCD_D5 = 22;
const int Output::LCD_D6 = 21;
const int Output::LCD_D7 = 14;

void Output::init() {
    lcd = lcdInit(4, 20, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0);
    lcdClear(lcd);
    lcdPosition(lcd, 0, 0);
    lcdPuts(lcd, "MEME");
}

void Output::setVoltage(float voltage) {
    lock.lock();
    lcd_setVoltage(voltage);
    lock.unlock();
}

/// IMPL ///

void Output::lcd_setup() {
    lcdClear(lcd);
}

void Output::lcd_setVoltage(float v) {

}
