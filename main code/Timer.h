#ifndef TIMER_H
#define TIMER_H

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
    // variables for start, stop, elapsed
    int startTime;
    int endTime;
    int elapsedTime;

public:
    // basic timer manipulation functions
    void start();

    void stop();

    void setNonBlockingInput();

    void restoreTerminal();


};


#endif // TIMER_H