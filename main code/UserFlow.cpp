#include "UserFlow.h"
#include "DataManager.h"

////////////////////////////////////////////////////////
//////////////  MEOW intro screens MEOW  ///////////////
////////////////////////////////////////////////////////

// first screen user sees "Press any button to continue"
void introScreens::startScreen() {

    Timer terminalModifier; // some terminal modifying functions are in the timer class *wink* only look at the object name not the class

    terminalModifier.clearScreen();
    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered("Welcome to Jon's Timer App.");
    terminalModifier.printCentered("Press any button to continue!");
    cout << endl << endl;

} 

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
    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered("Press any button to generate a scramble:");
    terminalModifier.printCentered("(esc to go to main menu)");

        cout << endl;
        cout << endl;

    // grabs new scramble from scramble object, returns a string, then prints centered
    pookie.newScramble();
    str = pookie.getScramble();
    terminalModifier.printCentered(str);

    // user presses any button to generate a new scramble, if they hit escape they back out of the screen going into main screen
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
            cout << endl << endl << endl << endl << endl << endl;
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
top:
    Timer terminalModifier;
    algorithmPracticeScreens algoPracticeSwitch;
    char c = 0;

    terminalModifier.clearScreen();

        cout << endl << endl << endl << endl << endl << endl;
    
        terminalModifier.printCentered("Algorithm Practice");
        terminalModifier.printCentered("(esc to return to main screen)");

        cout << endl;
        cout << endl;

        terminalModifier.printTwoColumns("OLL (o)", "PLL (p)");
        terminalModifier.printTwoColumns("Create Algorithm (c)", "Edit Algorithms (e)");

    // while loop to decide between OLL/PLL practice, edit algorithm or create algorithm (last two not working rn)
    while (true) {
        terminalModifier.setNonBlockingInput();

        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 'o') {
            isOll = true;
            opll();
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 'p') {
            isOll = false;
            opll(); // calls the same function as oll but the truth value is what makes the difference
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 'c') {
            own();
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 'e') {
            editAlgs();
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 27) { // escape to exit
            c = 0;
            terminalModifier.restoreTerminal();
            return;
        }
    }
    terminalModifier.restoreTerminal();
}

// when oll is called it just runs through the same system of actions as PLL but i decieded to duplicate my code
// because it looks better to have oll() and pll() above
// anyways this method calls navigator where the user chooses the algorithm category, algNavigator where the user chooses the specific sub-algorithm
// then fromSolved where the user gets to see how to get to the algorithm ascii from a solved state, then main timer so the user can set a time, save it, and see their data later
void algorithmPracticeScreens::opll() {
StartOfOPll:
    Timer terminalModifier;
    string algName;
    string specificAlgName;
    char c = 0;
    string returnStatement;
    string returnStatement2;

    // gameplay loop
    while (true) {
        algName = navigator();

        if (algName == "") { // if you esc out of nav you leave to main menu
            return;
        }

algNavigator:
        specificAlgName = algNavigator(algName);

        if (specificAlgName == "") { // if you esc out of algNav you go back to nav
            continue;
        }

        while (true) {

            returnStatement = splashScreen(specificAlgName);

            if (returnStatement == "F") {
                goto algNavigator;
            }

            returnStatement2 = fromSolved(specificAlgName);

            if (returnStatement2 == "") {
                terminalModifier.restoreTerminal();
                continue;
            }


            mainTimer(specificAlgName);
        }
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

// navigator goes through oll/pll algorithms by seeing if the user chose oll/pll, then pulling that speific file data
// the navigator displays the algorithm  categoryon screen, if the user hits enter then that is the users choice, if not
// then the user can hit space to continue searching
string algorithmPracticeScreens::navigator() {
    DataManager moo;
    Timer terminalModifer;
    char c = 0;
    string algName;

    terminalModifer.setNonBlockingInput();
    int counter = 0;

    if(!moo.fileInfoHolder.empty()) { // if the vector has something
        moo.fileInfoHolder.clear();
    }

    if (isOll) {
        moo.vectorFileInfo("Algorithms", "ollAlgs"); // send all of the information form the ollAlgs file to the moo vector
    } else {
        moo.vectorFileInfo("Algorithms", "pllAlgs"); // send all of the information form the pllAlgs file to the moo vector
    }

reprint_w_new_values:
    // for printing
    terminalModifer.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    // casual prints
    terminalModifer.printCentered("Algorithm Navigator");
    cout << endl;
    terminalModifer.printCentered("Choose what OLL Algorithm category you want");
    terminalModifer.printCentered("Space for next, Enter to choose");
        
    cout << endl << endl << endl;

    // prints alg category
    terminalModifer.printCentered(moo.fileInfoHolder[counter]);
    algName = moo.fileInfoHolder[counter];


    while (true) {
        c = 0; // for std input

        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        // conditional control for loops/ending

        // if spacebar
        if (c == 32) {
            counter++;
            c = 0;

            if(counter > moo.fileInfoHolder.size()) {
                counter = 0;
            }

            goto reprint_w_new_values;
        }

        if (c == 27) { // escape for leaving
            c = 0;
            return "";
        }

        // if enter
        if (c == 10) {
            terminalModifer.restoreTerminal();
            c = 0;
            return algName;
        }
    }

    terminalModifer.restoreTerminal();
    return algName;
}

// alg navigator works by taking the alg category, then searching the algPhotos file, parsing one string at a time
// then separating the string into specificAlgName, alg, and aglAscii -- this is used for display and for determining the specific sub-algoirthm
// the determining is done the same way navigaor determines
string algorithmPracticeScreens::algNavigator(string algName) {
    DataManager moo;
    Timer terminalModifer;
    string specificAlgName, alg, algAscii;
    char c = 0;

    vector<string> tempVec;

    terminalModifer.setNonBlockingInput();
    int counter = 0;

    if(!moo.fileInfoHolder.empty()) { // if the vector has something
        moo.fileInfoHolder.clear();
    }

    if (isOll) {
        moo.vectorFileInfo("Algorithms", "ollAlgPhotos"); // send send specific data into vector

        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            string holder = moo.fileInfoHolder[x];
            holder = holder.substr(0, holder.find(":"));
            
            if (algName == holder.substr(0, holder.length()-2)) {
                tempVec.push_back(moo.fileInfoHolder[x]);
            }
        }

    } else {
        moo.vectorFileInfo("Algorithms", "pllAlgPhotos"); // send send specific data into vector

        // processing for isolating the only related algorithms

        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            if (algName.substr(0, 1) == moo.fileInfoHolder[x].substr(0,1)) {
                tempVec.push_back(moo.fileInfoHolder[x]);
            }
        }
    }

reprint_w_new_values:

    terminalModifer.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    if(tempVec.size() == 1) { // only if the alg category has one specific algorithm (that is just your choice)
        terminalModifer.printCentered("Algorithm Navigator");
        cout << endl;
        terminalModifer.printCentered("Press enter to view");
        terminalModifer.printCentered("from a solved position");
    } else {
        terminalModifer.printCentered("Algorithm Navigator");
        cout << endl;
        terminalModifer.printCentered("What Algorithm do you want to practice?");
        terminalModifer.printCentered("Space for next, Enter to proceed to timer screen");
        terminalModifer.printCentered("Esc to exit");
    }

    // create a string stream out of every data string thats pulled in, this will get split into specific name, algorithm, and ascii
    stringstream ss(tempVec[counter]);

    getline(ss, specificAlgName, ':');
    getline(ss, alg, ':');
    getline(ss, algAscii);

    // supid string when printed doesnt count \n so had to turn it into \\n
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

    while (true) {
        c = 0;        
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        // conditional control for loops/ending

        if (c == 32) { // space for next
            counter++;
            c = 0;

            if(counter > tempVec.size()-1) {
                counter = 0;
            }

            goto reprint_w_new_values;
        }

        if (c == 27) { // escape for leaving
            c = 0;
            return "";
        }

        if (c == 10) { // enter to choose
            tempVec.clear();
            terminalModifer.restoreTerminal();
            break;
        }
    }
    terminalModifer.restoreTerminal();
    return specificAlgName;
}

// from solved will go to the fromSolved.txt files and grab if its oll/pll, then it will compare the algorithm that was chosen
// with the algorithms in the respective algphotos txt and will find the correct data to get to an algorithm from a solved state
string algorithmPracticeScreens::fromSolved(string algName) {
    DataManager moo;
    Timer terminalModifer;
    char c = 0;

    string temp; // holds alg from file
    string specName; // holds alg name
    string fromAlg; // holds algorithm

    if(!moo.fileInfoHolder.empty()){ // if the vector has something
            moo.fileInfoHolder.clear();
        }

    if(isOll) {
        moo.vectorFileInfo("Algorithms", "ollFromSolved");
    } else {
        moo.vectorFileInfo("Algorithms", "pllFromSolved");
    }

    // just to grab the single algorithm that has that name
    for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
        if (algName.substr(0, 3) == moo.fileInfoHolder[x].substr(0,3)) {
            temp = moo.fileInfoHolder[x];
        }
    }

    terminalModifer.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    terminalModifer.printCentered("From Solved");
    cout << endl;
    terminalModifer.printCentered("This is how you get to the algorithm");
    terminalModifer.printCentered("from a solved position");
    terminalModifer.printCentered("Enter to start timer");

    stringstream ss(temp);

    getline(ss, specName, ':');
    getline(ss, fromAlg);

    cout << endl << endl << endl;
    terminalModifer.printCentered(specName);
    cout << endl;
    terminalModifer.printCentered(fromAlg);

    terminalModifer.setNonBlockingInput();
    // user interaciton loop
    while (true) {
        c = 0;

        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 10) {
            break;
        }

        if (c == 27) {
            terminalModifer.restoreTerminal();
            return "";
        }

    }
    terminalModifer.restoreTerminal();
    return "meow";
}

string algorithmPracticeScreens::splashScreen(string specificAlgName) {
    Timer terminalModifier;
    DataManager dataMod;
    string algType;
    char c = 0;

    if(!dataMod.fileInfoHolder.empty()) { // if the vector has something
        dataMod.fileInfoHolder.clear();
    }

    if (isOll) {
        algType = "oll";
    } else {
        algType = "pll";
    }
refresh_the_screen:
    long long lasttime = 0;
    long long pbtime = 0;
    string formattedTime;
    string pbString = "PB: ";
    string ao5String;
    string ao10String;

    terminalModifier.clearScreen();
    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered(specificAlgName);
    cout << endl;

    lasttime = dataMod.getLatestAlgTime(algType, specificAlgName);
    TimeSpan lastSpan(lasttime); // this turns long long ms into a timespan .grabTime will return the time as a string
    formattedTime = lastSpan.grabTime();

    terminalModifier.printCentered(formattedTime);
    cout << endl << endl;

    pbtime = dataMod.grabPB(algType, specificAlgName);
    TimeSpan pbSpan(pbtime);
    pbString += pbSpan.grabTime();

    // PLACEHOLDER FOR THE AVERAGES AND THINGS OF THAT NATURE
    terminalModifier.printTwoColumns(pbString, "Ao5:");
    terminalModifier.printTwoColumns("Ao10:", "Ao100:");

    cout << endl << endl;

    terminalModifier.printCentered("Press any button to proceed seeing it from a solved position");
    terminalModifier.printCentered("u to undo last solve");
    terminalModifier.printCentered("Esc to go back");

    terminalModifier.setNonBlockingInput(); // sets raw mode

    while (true) {
        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 27) {
            return "F"; // escape to menu
        }  else if (c == 117) { // undo button
            dataMod.undoTime(algType, specificAlgName);
            goto refresh_the_screen;
        } else if (c > 0) {
            return "T";
        }

    }

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
void algorithmPracticeScreens::mainTimer(string specificAlgname) {
    string algType;
    Timer timer;
    DataManager mooski;
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char date[50];

    if (isOll) {
        algType = "oll";
    } else {
        algType = "pll";
    }

    long long finalTime;

    timer.runTimer(actualAlgorithm);

    finalTime = timer.returnFinalTime();

    strftime(date, 50, "%m/%d/%y", &datetime);

    mooski.saveAlgTime(algType, specificAlgname, finalTime, date);
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