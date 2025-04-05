// this will only include the time scaler one time per compilation unit
#pragma once

#include <iostream>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace chrono;

// this program will 
struct TimeSpan {
    int minutes;
    int seconds;
    int milliseconds;

    TimeSpan(long long totalMilliseconds);

    void print() const;
};