#include "UserFlow.h"
#include "DataManager.h"

#include <filesystem>
#include <iostream>

int main() {
    // dont worry about this
    string stopProgram = "";
    DataManager moo;
    Timer meow;
    Scramble algorithm; 
    char c = 0;

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
        cout << endl << endl << endl << endl << endl << endl;

        meow.printCentered("Type in one of the letters to pick between the options:");
        meow.printCentered("(esc to quit the app)");

        cout << endl;
        cout << endl;

        meow.printTwoColumns("Scrambler (s)", "Timer (t)");
        meow.printTwoColumns("Algorithm Practice (a)", "Data visualizer (d)");

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
    

    return 0;
}