#ifndef TIMER_H
#define TIMER_H

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
    long long elapsedTime;

public:
    // basic timer manipulation functions
    void start();

    // returns elapsed time
    void stop();

    void setNonBlockingInput();

    void restoreTerminal();

    void printTime();


};

#endif // TIMER_H