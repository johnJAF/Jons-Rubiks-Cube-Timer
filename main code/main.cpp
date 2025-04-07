#include "Timer.h"
#include "Scramble.h"


int main() {
    string stopProgram = "";
    Timer meow;
    Scramble algorithm; 

    // run the program until stop
    while (true) {
        cout << "Enter q to quit, to enter the timer, press anything on the keyboard: ";

        getline(cin, stopProgram);

        if (stopProgram == "q") {
            break;
        }

        meow.runTimer();
    }

    algorithm.newScramble();
    algorithm.print();
    algorithm.newScramble();
    algorithm.print();
    algorithm.newScramble();
    algorithm.print();
    
    algorithm.setScramble();

    algorithm.setOrientation();
    algorithm.print();
    cout << algorithm.getOrientation();

    return 0;
}