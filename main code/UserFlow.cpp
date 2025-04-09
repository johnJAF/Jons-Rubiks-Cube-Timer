#include "UserFlow.h"

////////////////////////////////////////////////////////
//////////////  MEOW intro screens MEOW  ///////////////
////////////////////////////////////////////////////////

// first screen user sees "Press any button to continue"
char introScreens::startScreen() {

    Timer terminalModifier;

    terminalModifier.setNonBlockingInput();
    char c = 0;
    
    terminalModifier.clearScreen();
    terminalModifier.printCentered("Welcome to Jon's Timer App.");
    terminalModifier.printCentered("Press any button to continue!");

    while (true) {
        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        // if any byte gets read from the terminal input then its gonna stop the program.
        if (bytesRead > 0) {
            break;
        }
        
    }
    terminalModifier.restoreTerminal();

    // opens up the main screen after user hits a random button to continue.
    char meow = mainScreen();

    return meow;
}

// second screen user sees, shows all four options between scrambler, timer, datavisualizer, alogirthmpractice
char introScreens::mainScreen() {
    Timer terminalModifier;
    terminalModifier.clearScreen();
    char optionChosen = 0;
    char c = 0;

    terminalModifier.printCentered("Type in one of the letters to pick between the options:");



        cout << endl;
        cout << endl;


    terminalModifier.printTwoColumns("Scrambler (s)", "Data visualizer (d)");
    terminalModifier.printTwoColumns("Algorithm Practice (a)", "Timer (t)");

    terminalModifier.setNonBlockingInput();

    while (true) {
        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        // if any byte gets read from the terminal input then its gonna stop the program.
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
        }
    }
    terminalModifier.restoreTerminal();

    return optionChosen;

}

////////////////////////////////////////////////////////
//////////////  MEOW scramble screen MEOW  /////////////
////////////////////////////////////////////////////////

// scramble screen main scren
void scrambleScreen::mainScreen() {
    cout << "this is the scramble screen";
}

////////////////////////////////////////////////////////
//////////////  MEOW algoPractice MEOW  ////////////////
////////////////////////////////////////////////////////

void algorithmPracticeScreens::mainScreen() {
    cout << "this is the algorithm practice screen";
}

void algorithmPracticeScreens::chooseOption() {

}

void algorithmPracticeScreens::oll() {

}

void algorithmPracticeScreens::pll() {

}

void algorithmPracticeScreens::own() {

}

void algorithmPracticeScreens::editAlgs() {

}

// this navigator screen will be used 4 times in choosing what name of algorithm/photo of algorithm for OLL/PLL
// uses isOLL
void algorithmPracticeScreens::navigator() {

}

// pulls from dataset that checks what algorithm you're doing
// uses isOll
void algorithmPracticeScreens::fromSolved() {

}

// just in case while you were solving you made some mistake and you want to remove the very last solve instance.
void algorithmPracticeScreens::undoSolve() {

}

// own
void algorithmPracticeScreens::algorithmName() {

}

void algorithmPracticeScreens::typeInAlgMoves() {

}

void algorithmPracticeScreens::drawMap() {

}

// creates a timer instance based on algorithm chosen, saves it to that respective file
// different baesd on isOll. Uses data vizualizer object code to show PB, Ao5, Ao12.
void algorithmPracticeScreens::mainTimer() {

}

////////////////////////////////////////////////////////
//////////////  MEOW dataVisualizer MEOW  //////////////
////////////////////////////////////////////////////////


void dataVisualizerScreen::mainScreen() {
    cout << "this is the data visualizer screen";
}

void dataVisualizerScreen::fileDisplay() {

}

void dataVisualizerScreen::fileSearch() {

}

void dataVisualizerScreen::fileCheck() {

}

// this might have to run some python scripts that can display all of the file data chosen.
void dataVisualizerScreen::displayData() {

}

////////////////////////////////////////////////////////
//////////////  MEOW timer screen MEOW  ////////////////
////////////////////////////////////////////////////////

void timerScreen::mainScreen() {
    cout << "this is the timer screen";
}

// dynamically creates a session if the file isnt there
void timerScreen::newSession() {

}

// opens session up
void timerScreen::previousSession() {

}

// displays all session files - probably using data visualizer
void timerScreen::sessionManager() {

}
void timerScreen::edit() {

}
void timerScreen::del() {

}

void timerScreen::mainTimer() {

}
void timerScreen::undo() {

}