#include "Timer.h"


int main() {
    string stopProgram = "";
    Timer meow;

    // run the program until stop
    while (true) {
        cout << "Enter q to quit, anything else to continue: ";
        
        getline(cin, stopProgram);

        if (stopProgram == "q") {
            break;
        }

        meow.runTimer();
    }
    
    return 0;
}