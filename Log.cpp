//Team 401 Vision Processing
//(Ported from the preseason code)
//File: Log.cpp
//Description: Provides functions for logging data and printing it to the console
//Author: Cameron Earle and Liam Lawrence

#include "Log.hpp"

#include <iostream>
#include <string>
#include <mutex>
#include <ios>


Log::Level Log::useLevel = Log::Level::INFO;
bool Log::useFile = false;
bool Log::doDebug = true;
std::mutex Log::fileLock;
std::mutex Log::logLock;
std::ofstream Log::file;

/* Function init
 * Argument [Level level_]: The minimum level to write to a file
 * Argument [bool useFile_]: Whether or not to write data to a file
 * Argument [string filePath_]: The path of the file to use
 * Description: Initialize the logger for use across the program.  This should be done on the first line of main()
 */
void Log::init(Level level_, bool useFile_, std::string filePath_) {
    useLevel = level_;
    useFile = useFile_;
    if (useFile) { //If we should use a file
        file.open(filePath_, std::ios::app); //Open the log file in append mode
    }
}

/* Function setDoDebug
 * Argument [bool value]: The value to set the flag to
 * Description: Sets whether or not we should print out DEBUG statements in the log.  Should increase performance when debug mode is off
 */
void Log::setDoDebug(bool value) {
    doDebug = value;
    if (doDebug) {
        i("Log", "DEBUG messages are now enabled");
    } else {
        i("Log", "DEBUG messages are now disabled");
    }
}

/* Function getDateTime
 * Description: Private function to get a formatted time string
 * Returns [string]: The time string that represents the current time
 */
std::string Log::getDateTime() {
    //As we are building without boost, we can't include the date and time, so we will replace the date and time with
    //the name of the program instead
    return "[CartDS]";
}

/* Function writeToFile
 * Argument [string outString_]: The string to write to the file
 * Description: Private function to write log data to a file
 */
void Log::writeToFile(std::string outString_) {
    fileLock.lock(); //Lock this function so we don't get IO errors
    file << outString_ << "\n"; //Write the line to the file
    fileLock.unlock(); //Unlock this function so more log calls can be made
}

/* Function close
 * Description: Close the logger, and the file if applicable
 */
void Log::close() {
    if (useFile) { //If we are using a file
        file.close(); //Close the file
    }
}

/* Function d
 * Argument [string ld_]: The log descriptor, usually the name of the class calling the function
 * Argument [string data_]: The data to be logged
 * Description: Logs data at the DEBUG level
 */
void Log::d(std::string ld_, std::string data_) {
    if (doDebug) { //If we should print DEBUG messages
        logLock.lock(); //Lock this function so messages sequence correctly
        std::string outString = getDateTime() + " [DEBUG] [" + ld_ + "] " + data_; //Build the string with the time and level
        std::cout << outString << std::endl; //Print the line to the standard out
        if (useFile && useLevel <= Level::DEBUG) { writeToFile(outString); } //If we are using a file and the set log level matches the current one, write to the file
        logLock.unlock(); //Unlock this function so more log calls can be made
    }
}

/* Function i
 * Argument [string ld_]: The log descriptor, usually the name of the class calling the function
 * Argument [string data_]: The data to be logged
 * Description: Logs data at the INFO level
 */
void Log::i(std::string ld_, std::string data_) {
    logLock.lock(); //Lock this function so messages sequence correctly
    std::string outString = getDateTime() + " [INFO] [" + ld_ + "] " + data_; //Build the string with the time and level
    std::cout << outString << std::endl; //Print the line to the standard out
    if (useFile && useLevel <= Level::INFO) { writeToFile(outString); } //If we are using a file and the set log level matches the current one, write to the file
    logLock.unlock(); //Unlock this function so more log calls can be made
}

/* Function w
 * Argument [string ld_]: The log descriptor, usually the name of the class calling the function
 * Argument [string data_]: The data to be logged
 * Description: Logs data at the WARNING level
 */
void Log::w(std::string ld_, std::string data_) {
    logLock.lock(); //Lock this function so messages sequence correctly
    std::string outString = getDateTime() + " [WARNING] [" + ld_ + "] " + data_; //Build the string with the time and level
    std::cerr << outString << std::endl; //Print the line to the error out
    if (useFile && useLevel <= Level::WARNING) { writeToFile(outString); } //If we are using a file and the set log level matches the current one, write to the file
    logLock.unlock(); //Unlock this function so more log calls can be made
}

/* Function e
 * Argument [string ld_]: The log descriptor, usually the name of the class calling the function
 * Argument [string data_]: The data to be logged
 * Description: Logs data at the ERROR level
 */
void Log::e(std::string ld_, std::string data_) {
    logLock.lock(); //Lock this function so messages sequence correctly
    std::string outString = getDateTime() + " [ERROR] [" + ld_ + "] " + data_; //Build the string with the time and level
    std::cerr << outString << std::endl; //Print the line to the error out
    if (useFile && useLevel <= Level::ERROR) { writeToFile(outString); } //If we are using a file and the set log level matches the current one, write to the file
    logLock.unlock(); //Unlock this function so more log calls can be made
}

/* Function x
 * Argument [string ld_]: The log descriptor, usually the name of the class calling the function
 * Argument [string data_]: The data to be logged
 * Description: Logs data at the EXCEPTION level
 */
void Log::x(std::string ld_, std::string data_) {
    logLock.lock(); //Lock this function so messages sequence correctly
    std::string outString = getDateTime() + " [EXCEPTION] [" + ld_ + "] " + data_; //Build the string with the time and level
    std::cerr << outString << std::endl; //Print the line to the error out
    if (useFile && useLevel <= Level::EXCEPTION) { writeToFile(outString); } //If we are using a file and the set log level matches the current one, write to the file
    logLock.unlock(); //Unlock this function so more log calls can be made
}

/* Function wtfomgy
 * Argument [string ld_]: The log descriptor, usually the name of the class calling the function
 * Argument [string data_]: The data to be logged
 * Description: Logs data at the WHAT THE FRICK, OH MY GOD WHY? level (for things that really shouldn't ever happen)
 */
void Log::wtfomgy(std::string ld_, std::string data_) {
    logLock.lock(); //Lock this function so messages sequence correctly
    std::string outString = getDateTime() + " [WHAT THE FRICK, OH MY GOD WHY?] [" + ld_ + "] " + data_; //Build the string with the time and level
    std::cerr << outString << std::endl; //Print the line to the error out
    if (useFile) { writeToFile(outString); } //There is technically no WTFOMGY level, so just write it if we are using a file
    logLock.unlock(); //Unlock this function so more log calls can be made
}