#include "Timer.h"


int main() {
    string stopProgram = "";

    // run the program until stop
    while (true) {
        cout << "Enter q to quit, anything else to continute: ";
        cin >> stopProgram;

        if (stopProgram == "q") {
            break;
        }

        Timer meow;

        meow.runTimer();

    }
    
    return 0;
}