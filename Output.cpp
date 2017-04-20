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
    lcd_setup();
}

void Output::setVoltage(float voltage) {
    lock.lock();
    lcd_setVoltage(voltage);
    lock.unlock();
}

void Output::setPower(int power) {
    lock.lock();
    lcd_setPower(power);
    lock.unlock();
}

void Output::setMode(int mode) {
    lock.lock();
    lcd_setMode(mode);
    lock.unlock();
}

/// IMPL ///

void Output::lcd_setup() {
    lcdClear(lcd);
    lcdPosition(lcd, 0, 0); //Zero the cursor
    lcdPuts(lcd, "XxX_TEAM401 CART_XxX"); //Write the header
    lcdPosition(lcd, 1, 0); //Move to the second row
    lcdPuts(lcd, "Voltage: XX.XX");
    lcdPosition(lcd, 2, 0); //Move to the third row
    lcdPuts(lcd, "Power:   XXX%");
    lcdPosition(lcd, 3, 0); //Move to the fourth row
    lcdPuts(lcd, "Mode:    XXXXXXXX");
}

void Output::lcd_setVoltage(float v) {
    lcdPosition(lcd, 1, 9);
    lcdPrintf(lcd, "%.2f", v);
}

void Output::lcd_setPower(int p) {
    lcdPosition(lcd, 2, 9);
    lcdPuts(lcd, std::to_string(p).c_str());
}

void Output::lcd_setMode(int m) {
    lcdPosition(lcd, 3, 9);
    switch (m) {
        case 0:
            lcdPuts(lcd, "ENABLED");
            break;
        case 1:
            lcdPuts(lcd, "DISABLED");
            break;
        case 2:
            lcdPuts(lcd, "E-STOPPED");
            break;
    }
}