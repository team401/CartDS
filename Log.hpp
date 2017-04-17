//Team 401 Vision Processing
//(Ported from the preseason code)
//File: Log.hpp
//Description: Provides functions for logging data and printing it to the console
//Author: Cameron Earle and Liam Lawrence

#ifndef PROJECT_LOG_HPP
#define PROJECT_LOG_HPP


#include <string>
#include <mutex>
#include <fstream>

using namespace std;

class Log {
public:
    enum Level {
        DEBUG=0,
        INFO=1,
        WARNING=2,
        ERROR=3,
        EXCEPTION=4
    };
    static void init(Level level_, bool useFile_, std::string filePath_="vision.log");
    static void setDoDebug(bool value);
    static void d(string ld_, std::string data_); //DEBUG
    static void i(string ld_, std::string data_); //INFO
    static void w(string ld_, std::string data_); //WARNING
    static void e(string ld_, std::string data_); //ERROR
    static void x(string ld_, std::string data_); //EXCEPTION
    static void wtfomgy(string ld_, string data_); //WHAT THE FRICK, OH MY GOD WHY?
    static void close();
private:
    static string getDateTime();
    static void writeToFile(string outString_);
    static bool useFile;
    static bool doDebug;
    static Level useLevel;
    static mutex fileLock;
    static mutex logLock;
    static ofstream file;
};


#endif //PROJECT_LOG_HPP
