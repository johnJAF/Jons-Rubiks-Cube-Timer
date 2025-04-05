#include "TimeScaler.h"

TimeSpan::TimeSpan(long long totalMilliseconds) {
        minutes = totalMilliseconds / 60000;
        seconds = (totalMilliseconds % 60000) / 1000;
        milliseconds = totalMilliseconds % 1000;
    }


void TimeSpan::print() const {
    cout << setfill('0') << setw(2) << minutes << ":"
                << setfill('0') << setw(2) << seconds << ":"
                << setfill('0') << setw(3) << milliseconds << "\n";
}