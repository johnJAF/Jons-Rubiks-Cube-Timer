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

    // while loop to decide what feature to choose from

    while (true) {
        terminalModifier.clearScreen();
    
        terminalModifier.printCentered("Algorithm Practice");
        terminalModifier.printCentered("(esc to return to main screen)");

        cout << endl;
        cout << endl;

        terminalModifier.printTwoColumns("OLL (o)", "PLL (p)");
        terminalModifier.printTwoColumns("Create Algorithm (c)", "Edit Algorithms (e)");

        terminalModifier.setNonBlockingInput();

        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 'o') {
            isOll = true;
            oll();
            terminalModifier.restoreTerminal();
        } else if (c == 'p') {
            isOll = false;
            pll();
        } else if (c == 'c') {
            own();
            terminalModifier.restoreTerminal();
        } else if (c == 'e') {
            editAlgs();
            terminalModifier.restoreTerminal();
        } else if (c == 27) { // escape to exit
            c = 0;
            return;
        }
    }
    terminalModifier.restoreTerminal();
}


void algorithmPracticeScreens::oll() {
    Timer terminalModifier;
    if(isOll == true) { // assertion for the code to run
        string algName;
        string specificAlgName;
        char c = 0;

        algName = navigator();
        cout << algName << endl;
        specificAlgName = algNavigator(algName);
        cout << specificAlgName << endl;

        if (specificAlgName == "") {
            return;
        }

        fromSolved(specificAlgName);
        mainTimer(specificAlgName);

        while (true) {
            terminalModifier.setNonBlockingInput(); // sets raw mode

            c = 0;
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifier.clearScreen();
            cout << endl << endl << endl << endl;
            terminalModifier.printCentered("Continue practicing? y/n");

            if (c == 'n') {
                terminalModifier.restoreTerminal();
                return;
            } else if (c == 'y') {
                fromSolved(specificAlgName);
                mainTimer(specificAlgName);
            }
        }
        
    } else {
        cout << "Something is wrong with the isOll truth value";
    }
}

void algorithmPracticeScreens::pll() {
    Timer terminalModifier;
    if(isOll == false) {
        string algName;
        string specificAlgName;
        char c = 0;

        algName = navigator();
        specificAlgName = algNavigator(algName);

        if (specificAlgName == "") {
            return;
        }

        fromSolved(specificAlgName);
        mainTimer(specificAlgName);

        while (true) {
            terminalModifier.setNonBlockingInput(); // sets raw mode

            c = 0;
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifier.clearScreen();
            cout << endl << endl << endl << endl;
            terminalModifier.printCentered("Continue practicing? y/n");

            if (c == 'n') {
                terminalModifier.restoreTerminal();
                return;
            } else if (c == 'y') {
                fromSolved(specificAlgName);
                mainTimer(specificAlgName);
            }
        }
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
    string algName;

    if (isOll == true) {
        terminalModifer.setNonBlockingInput();
        int counter = 0;
        
        if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

        moo.vectorFileInfo("Algorithms", "ollAlgs"); // send all of the information form the pllAlgs file to the moo vector

        while (true) {
            c = 0;

            // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifer.clearScreen();

            // casual prints
            terminalModifer.printCentered("Algorithm Navigator");
            cout << endl;
            terminalModifer.printCentered("Choose what OLL Algorithm category you want");
            terminalModifer.printCentered("Space for next, Enter to choose");
                
            cout << endl << endl << endl;

            terminalModifer.printCentered(moo.fileInfoHolder[counter]);
            algName = moo.fileInfoHolder[counter];

            // conditional control for loops/ending

            if(counter > moo.fileInfoHolder.size()-1) {
                counter = 0;
            }

            if (c == 32) {
                counter++;
                c = 0;
                continue;
            }

            if (c == 10) {
                terminalModifer.restoreTerminal();
                c = 0;
                return algName;
            }
        }
        terminalModifer.restoreTerminal();
        return algName;
    } else { //pll
        terminalModifer.setNonBlockingInput();
        int counter = 0;
        
        if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

        moo.vectorFileInfo("Algorithms", "pllAlgs"); // send all of the information form the pllAlgs file to the moo vector

        while (true) {
            c = 0;

            // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifer.clearScreen();

            // casual prints
            terminalModifer.printCentered("Algorithm Navigator");
            cout << endl;
            terminalModifer.printCentered("Choose what Pll Algorithm category you want");
            terminalModifer.printCentered("Space for next, Enter to choose");
                
            cout << endl << endl << endl;

            terminalModifer.printCentered(moo.fileInfoHolder[counter]);
            algName = moo.fileInfoHolder[counter];

            // conditional control for loops/ending

            if(counter > moo.fileInfoHolder.size()-1) {
                counter = 0;
            }

            if (c == 32) {
                counter++;
                c = 0;
                continue;
            }

            if (c == 10) {
                terminalModifer.restoreTerminal();
                c = 0;
                return algName;
            }
        }
        terminalModifer.restoreTerminal();
        return algName;
    }
}

string algorithmPracticeScreens::algNavigator(string algName) {
    DataManager moo;
    Timer terminalModifer;
    string specificAlgName, alg, algAscii;
    char c = 0;

    vector<string> tempVec;


    if (isOll == true) {
        terminalModifer.setNonBlockingInput();
        int counter = 0;

        if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

        moo.vectorFileInfo("Algorithms", "ollAlgPhotos"); // send the fille algPhoto data into the 

        // processing for isolating the only related algorithms

        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            string holder = moo.fileInfoHolder[x];
            holder = holder.substr(0, holder.find(":"));
            
            if (algName == holder.substr(0, holder.length()-2)) {
                tempVec.push_back(moo.fileInfoHolder[x]);
            }
        }

        // this can be used to parse the photos
        while (true) {
            c = 0;

            terminalModifer.clearScreen();

            if(tempVec.size() == 1) {
                terminalModifer.printCentered("Algorithm Navigator");
                cout << endl;
                terminalModifer.printCentered("Press enter to see how to get to this");
                terminalModifer.printCentered("from a solved position");
            } else {
                terminalModifer.printCentered("Algorithm Navigator");
                cout << endl;
                terminalModifer.printCentered("What Algorithm do you want to practice?");
                terminalModifer.printCentered("Space for next, Enter to choose, Esc to exit");
            }
            
            // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
            
            // create a string stream out of every data string thats pulled in, this will get split into specific name, algorithm, and ascii
            stringstream ss(tempVec[counter]);

            getline(ss, specificAlgName, ':');
            getline(ss, alg, ':');
            getline(ss, algAscii);

            // supid string when printed doesnt count /n so had to turn it into //n
            size_t pos = 0;
            while ((pos = algAscii.find("\\n", pos)) != string::npos) {
                algAscii.replace(pos, 2, "\n");
            }

            // casual print
            cout << endl << endl << endl;
            terminalModifer.printCentered(specificAlgName);
            terminalModifer.printCentered(alg);
            actualAlgorithm = alg;

            cout << endl << algAscii;

            // conditional control for loops/ending

            if(counter > tempVec.size()-1) {
                counter = 0;
            }

            // if you hit a button its gonna grab next alg
            if (c == 32) {
                counter++;
                c = 0;
                continue;
            }

            if (c == 27) {
                c = 0;
                return "";
            }

            // if any byte gets read from the terminal input then its gonna stop the program.
            if (c == 10) {
                tempVec.clear();
                terminalModifer.restoreTerminal();
                break;
            }
        }
    terminalModifer.restoreTerminal();
    return specificAlgName;
    } else { //pll
        terminalModifer.setNonBlockingInput();
        int counter = 0;

        if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

        moo.vectorFileInfo("Algorithms", "pllAlgPhotos"); // send the fille algPhoto data into the 

        // processing for isolating the only related algorithms

        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            if (algName.substr(0, 1) == moo.fileInfoHolder[x].substr(0,1)) {
                tempVec.push_back(moo.fileInfoHolder[x]);
            }
        }

        // this can be used to parse the photos
        while (true) {
            c = 0;

            terminalModifer.clearScreen();

            if(tempVec.size() == 1) {
                terminalModifer.printCentered("Algorithm Navigator");
                cout << endl;
                terminalModifer.printCentered("Press enter to see how to get to this");
                terminalModifer.printCentered("from a solved position");
            } else {
                terminalModifer.printCentered("Algorithm Navigator");
                cout << endl;
                terminalModifer.printCentered("What Algorithm do you want to practice?");
                terminalModifer.printCentered("Space for next, Enter to choose, Esc to exit");
            }
            
            // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
            
            // create a string stream out of every data string thats pulled in, this will get split into specific name, algorithm, and ascii
            stringstream ss(tempVec[counter]);

            getline(ss, specificAlgName, ':');
            getline(ss, alg, ':');
            getline(ss, algAscii);

            // supid string when printed doesnt count /n so had to turn it into //n
            size_t pos = 0;
            while ((pos = algAscii.find("\\n", pos)) != string::npos) {
                algAscii.replace(pos, 2, "\n");
            }

            // casual print
            cout << endl << endl << endl;
            terminalModifer.printCentered(specificAlgName);
            terminalModifer.printCentered(alg);
            actualAlgorithm = alg;

            cout << endl << algAscii;

            // conditional control for loops/ending

            if(counter > tempVec.size()-1) {
                counter = 0;
            }

            // if you hit a button its gonna grab next alg
            if (c == 32) {
                counter++;
                c = 0;
                continue;
            }

            if (c == 27) {
                c = 0;
                return "";
            }

            // if any byte gets read from the terminal input then its gonna stop the program.
            if (c == 10) {
                tempVec.clear();
                terminalModifer.restoreTerminal();
                break;
            }
        }
    }
    terminalModifer.restoreTerminal();
    return specificAlgName;
}

// pulls from dataset that checks what algorithm you're doing
// uses isOll
void algorithmPracticeScreens::fromSolved(string algName) {
    DataManager moo;
    Timer terminalModifer;
    char c = 0;

    string temp; // holds alg from file
    string specName; // holds alg name
    string fromAlg; // holds algorithm

    cout << endl << "This is how you get to the algorithm from a solved state" << endl;

    if (isOll == true) {
        if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

        moo.vectorFileInfo("Algorithms", "ollFromSolved"); // send the fille algPhoto data into the 

        // just to grab the single algorithm that has that name
        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            if (algName.substr(0, 2) == moo.fileInfoHolder[x].substr(0,2)) {
                temp = moo.fileInfoHolder[x];
            }
        }

        while (true) {
            c = 0;
            
            terminalModifer.clearScreen();

            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifer.printCentered("From Solved");
            cout << endl;
            terminalModifer.printCentered("This is how you get to the algorithm");
            terminalModifer.printCentered("from a solved position");
            terminalModifer.printCentered("Enter to proceed to the timer");

            stringstream ss(temp);

            getline(ss, specName, ':');
            getline(ss, fromAlg);

            cout << endl << endl << endl;
            terminalModifer.printCentered(specName);
            terminalModifer.printCentered(fromAlg);

            if (c == 10) {
                break;
            }

        }
    } else { //pll
        //terminalModifer.setNonBlockingInput();

        if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

        moo.vectorFileInfo("Algorithms", "pllFromSolved"); // send the fille algPhoto data into the 

        // just to grab the single algorithm that has that name
        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            if (algName.substr(0, 2) == moo.fileInfoHolder[x].substr(0,2)) {
                temp = moo.fileInfoHolder[x];
            }
        }

        while (true) {
            c = 0;
            
            terminalModifer.clearScreen();

            ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

            terminalModifer.printCentered("From Solved");
            cout << endl;
            terminalModifer.printCentered("This is how you get to the algorithm");
            terminalModifer.printCentered("from a solved position");
            terminalModifer.printCentered("Enter to proceed to the timer");

            stringstream ss(temp);

            getline(ss, specName, ':');
            getline(ss, fromAlg);

            cout << endl << endl << endl;
            terminalModifer.printCentered(specName);
            terminalModifer.printCentered(fromAlg);

            if (c == 10) {
                break;
            }

        }

    }
    return;
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
    // TimeSpan meow(elapsedTime); this turns long long ms into a timespan .grabTime will return the time as a string
    Timer timer;

    timer.runTimer(actualAlgorithm);
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

void timerScreen::mainTimer(string session) {

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