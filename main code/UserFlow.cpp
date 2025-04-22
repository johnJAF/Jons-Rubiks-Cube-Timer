#include "UserFlow.h"
#include "DataManager.h"

////////////////////////////////////////////////////////
//////////////  MEOW intro screens MEOW  ///////////////
////////////////////////////////////////////////////////

// first screen user sees "Press any button to continue"
void introScreens::startScreen() {

    Timer terminalModifier;

    terminalModifier.clearScreen();
    terminalModifier.printCentered("Welcome to Jon's Timer App.");
    terminalModifier.printCentered("Press any button to continue!");
    cout << endl << endl;

} // branch test

// second screen user sees, shows all four options between scrambler, timer, datavisualizer, alogirthmpractice
void introScreens::mainScreen(char moo) {
    // all objects to take care of screen switching when an option is chosen.
    Timer terminalModifier;
    scrambleScreen scrambleSwitch;
    algorithmPracticeScreens algoPracticeSwitch;
    dataVisualizerScreen dataVisSwitch;
    timerScreen timeSwitch;
    char c = 0;

    char optionChosen = moo;  

    // every screen except scramble will have a repeating loop because they all have their own individual internal screens i think
    if (optionChosen == 's') {
        scrambleSwitch.mainScreen();
    } else if (optionChosen == 'a'){
        algoPracticeSwitch.mainScreen();
    } else if (optionChosen == 'd') {
        dataVisSwitch.mainScreen();
    } else if (optionChosen == 't') {
        timeSwitch.mainScreen();
    }
}

////////////////////////////////////////////////////////
//////////////  MEOW scramble screen MEOW  /////////////
////////////////////////////////////////////////////////

// scramble screen main scren
void scrambleScreen::mainScreen() {
    Timer terminalModifier;
    Scramble pookie;
    char c = 0;
    string str = "";

    terminalModifier.clearScreen();
    terminalModifier.printCentered("Press any button to generate a scramble:");
    terminalModifier.printCentered("(esc to go to main menu)");

        cout << endl;
        cout << endl;

    pookie.newScramble();
    str = pookie.getScramble();
    terminalModifier.printCentered(str);

    terminalModifier.setNonBlockingInput();

    while (true) {
        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        string holder;

        if (c > 0) {
            if (c == 27) {
                return;
            }
            terminalModifier.clearScreen();
            terminalModifier.printCentered("Press any button to generate a scramble:");
            terminalModifier.printCentered("(esc to go to main menu)");

            cout << endl;
            cout << endl;

            pookie.newScramble();
            holder = pookie.getScramble();
            terminalModifier.printCentered(holder);
            c = 0;
        }
    }
    terminalModifier.restoreTerminal();
}

////////////////////////////////////////////////////////
//////////////  MEOW algoPractice MEOW  ////////////////
////////////////////////////////////////////////////////

void algorithmPracticeScreens::mainScreen() {
    Timer terminalModifier;
    algorithmPracticeScreens algoPracticeSwitch;
    char c = 0;
    char optionChosen = 0;

    terminalModifier.clearScreen();
    
    terminalModifier.printCentered("Algorithm Practice");
    terminalModifier.printCentered("(esc to return to main screen)");

    cout << endl;
    cout << endl;

    terminalModifier.printTwoColumns("OLL (o)", "PLL (p)");
    terminalModifier.printTwoColumns("Create Algorithm (c)", "Edit Algorithms (e)");

    terminalModifier.setNonBlockingInput();

    // while loop to decide what feature to choose from

    while (true) {
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 'o') {
            optionChosen = c;
            isOll = true;
            oll();
            break;
        } else if (c == 'p') {
            optionChosen = c;
            isOll = false;
            pll();
            break;
        } else if (c == 'c') {
            optionChosen = c;
            own();
            break;
        } else if (c == 'e') {
            optionChosen = c;
            editAlgs();
            break;
        } else if (c == 27) { // escape to exit
            return;
        }
    }
    terminalModifier.restoreTerminal();
}


void algorithmPracticeScreens::oll() {
    if(isOll == true) { // assertion for the code to run
        string file;
        string finalFile;


        file = navigator(); // navigates through alg names
        finalFile = algNavigator(file); // navigates through alg photos

        fromSolved(finalFile); 
        mainTimer(finalFile);
        
    } else {
        cout << "Something is wrong with the isOll truth value";
    }
}

void algorithmPracticeScreens::pll() {
    if(isOll == false) { // assertion for the code to run
        string file;
        string finalFile;

        cout << endl << "PLL MEOW" << endl;
        file = navigator(); // navigates through alg names
        finalFile = algNavigator(file); // navigates through alg photos

        fromSolved(finalFile);
        mainTimer(finalFile);
    } else {
        cout << "Something is wrong with the isOll truth value";
    }
}

void algorithmPracticeScreens::own() {
    cout << endl << "OWN MEOW" << endl;
}

void algorithmPracticeScreens::editAlgs() {
    Timer terminalModifier;
    terminalModifier.clearScreen();
    cout << "This feature doesnt work homie";
}

// this navigator screen will be used 4 times in choosing what name of algorithm/photo of algorithm for OLL/PLL
// uses isOLL
string algorithmPracticeScreens::navigator() {
    DataManager moo;
    Timer terminalModifer;
    char c = 0;

    cout << endl << "I am the navigator" << endl;

    if (isOll == true) {
        cout << endl << "This is the OLL version" << endl;
    } else {
        string algName;


        terminalModifer.setNonBlockingInput();


        int counter = 0;
        while (true) {
            // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifer.clearScreen();

            terminalModifer.printCentered("Algorithm Navigator");
            cout << endl;
            terminalModifer.printCentered("Choose what Algorithm category you want");
            terminalModifer.printCentered("Space for next, Enter to choose");

            moo.vectorFileInfo("Algorithms", "pllAlgs");
                
            cout << endl << endl << endl;

            terminalModifer.printCentered(moo.fileInfoHolder[counter]);

            if(counter > moo.fileInfoHolder.size()-1) {
                counter = 0;
            }

            if(counter > moo.fileInfoHolder.size()-1) {
                counter = 0;
            }

            // if you hit a button its gonna grab next alg
            if (c == 32) {
                counter++;
                c = 0;
                continue;
            }

            // if any byte gets read from the terminal input then its gonna stop the program.
            if (c == 10) {
                return algName;
                break;
            }
        }
        terminalModifer.restoreTerminal();
    }

    return "";
}

string algorithmPracticeScreens::algNavigator(string file) {
    cout << endl << "I am the alg photo navigator" << endl;
    string algName, alg, algAscii;

    if (isOll == true) {
        cout << endl << "This is the OLL version" << endl;
    } else {
        cout << endl << "This is the PLL version" << endl;


        // this can be used to parse the photos
        // while (true) {
        //     // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        //     ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        //     for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
        //         stringstream ss(moo.fileInfoHolder[x]);

        //         getline(ss, algName, ':');

        //         if(x > moo.fileInfoHolder.size()-1) {
        //             x = 0;
        //         }
        //     }

        //     // if you hit a button its gonna grab next alg
        //     if (c == 32) {
        //         continue;
        //     }

        //     // if any byte gets read from the terminal input then its gonna stop the program.
        //     if (c == 10) {
        //         return algName;
        //         break;
        //     }
        // }
    }

    return "";
}

// pulls from dataset that checks what algorithm you're doing
// uses isOll
void algorithmPracticeScreens::fromSolved(string file) {
    cout << endl << "This is how you get to the algorithm from a solved state" << endl;
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
void algorithmPracticeScreens::mainTimer(string file) {
    Timer meow;

    meow.runTimer();
}

////////////////////////////////////////////////////////
//////////////  MEOW dataVisualizer MEOW  //////////////
////////////////////////////////////////////////////////


void dataVisualizerScreen::mainScreen() {
    Timer terminalModifier;
    terminalModifier.clearScreen();
    cout << endl << "this is the data visualizer screen";
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
    Timer terminalModifier;
    terminalModifier.clearScreen();
    cout << endl << "this is the timer screen";
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

void timerScreen::inspectionToggle() {
    if (toggleInspectionTime == true) {
        toggleInspectionTime = false;
    } else {
        toggleInspectionTime = true;
    }

}

bool timerScreen::getInspectionToggle() {
    return toggleInspectionTime;
}

void timerScreen::orientationToggle() {
    if (toggleOrientation == true) {
        toggleOrientation = false;
    } else {
        toggleOrientation = true;
    }
}

bool timerScreen::getOrientationToggle() {
    return toggleOrientation;
}

void timerScreen::undo() {

}