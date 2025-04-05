#include "Timer.h"
#include "Scramble.h"


int main() {
    string stopProgram = "";
    Timer meow;
    Scramble algorithm; 

    // run the program until stop
    while (true) {
        cout << "Enter q to quit, anything else to continue: ";
        
        getline(cin, stopProgram);

        if (stopProgram == "q") {
            break;
        }

        meow.runTimer();
    }

    algorithm.newScramble();
    algorithm.print();
    algorithm.setScramble();

    algorithm.setOrientation("rr");
    algorithm.print();
    cout << algorithm.getOrientation();

    return 0;
}