#pragma once

#include "TimeScaler.h"

#include <iostream>
#include <ctime>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>
#include <thread>     // for sleep
#include <chrono>     // for milliseconds

using namespace std;

// I want there to be timer objects for all of the different features
// eg: main timer for timing, individual timers for training exercises 
// perhaps they could store all of their information 
class Timer {
    using Clock = std::chrono::steady_clock;
    // variables for start, stop, elapsed
    Clock::time_point startTime;
    Clock::time_point stopTime;
    long long elapsedTime; // for printing at end of timer
    long long elapsedTimeForCurrent; // for printing on screen as timer runs

public:
    // basic timer manipulation functions
    void start();

    // returns elapsed time
    void stop();

    // used while timer is running - will grab curren time - starting time
    void elapsedCurrent();

    // will make the terminal throw typing settings out the window
    void setNonBlockingInput();

    // returns all terminal settings
    void restoreTerminal();

    // prints elapsed time
    void printTime();

    // uses elapsedCurrent to print constantly during main while loop
    void printCurrent();

    // clears the screen depending on system archetecture
    void clearScreen();


};
