#include "UserFlow.h"
#include "DataManager.h"

#include <filesystem>
#include <iostream>

// create file paths in case they dont exist

int main() {
    // dont worry about this
    DataManager bro;
    string stopProgram = "";
    Timer meow;
    Scramble algorithm; 
    char c = 0;

    bro.createDataDirectories();

    // this block of code takes care of the intro loop, just for the splash screen. 
    introScreens introSwitch;
    meow.setNonBlockingInput();

    introSwitch.startScreen();
    while (true) {
        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        // if any byte gets read from keyboard, it will move into the actual program loop
        if (bytesRead > 0) {
            break;
        }
    }
    meow.restoreTerminal();

    // this loop is going to take care of the feature choice. only stops when escape is pressed
    char optionChosen = 0;
    while (c != 27) {
        meow.clearScreen();
        
        char c = 0;

        meow.printCentered("Type in one of the letters to pick between the options:");
        meow.printCentered("(esc to quit the app)");

        cout << endl;
        cout << endl;

        meow.printTwoColumns("Scrambler (s)", "Data visualizer (d)");
        meow.printTwoColumns("Algorithm Practice (a)", "Timer (t)");

        meow.setNonBlockingInput();

        // while loop to decide what feature to choose from
        while (true) {
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            // choices choices
            if (c == 's') {
                optionChosen = c;
                break;
            } else if (c == 'a'){
                optionChosen = c;
                break;
            } else if (c == 'd') {
                optionChosen = c;
                break;
            } else if (c == 't') {
                optionChosen = c;
                break;
            } else if (c == 27) {
                return 0;
            }
        }
        meow.restoreTerminal();
        introSwitch.mainScreen(optionChosen);
    }
    
 
    
    
    // depending on the feature chosen, we're gonna run that feature.

    // while (true) {
    //     cout << "Enter q to quit, to enter the timer, enter anything on the keyboard: ";

    //     getline(cin, stopProgram);

    //     if (stopProgram == "q") {
    //         break;
    //     }

    //     meow.runTimer();
    // }

    // algorithm.newScramble();
    // algorithm.print();
    // algorithm.newScramble();
    // algorithm.print();
    // algorithm.newScramble();
    // algorithm.print();
    
    // algorithm.setScramble();

    // algorithm.setOrientation();
    // algorithm.print();
    // cout << algorithm.getOrientation();

    return 0;
}