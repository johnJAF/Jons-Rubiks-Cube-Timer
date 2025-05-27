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
void introScreens::mainScreen(const char moo) {
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
    navCounter = 0;
    algNavCounter = 0;
    char c = 0;

    terminalModifier.clearScreen();

        cout << endl << endl << endl << endl << endl << endl;
    
        terminalModifier.printCentered("Algorithm Practice");
        terminalModifier.printCentered("(esc to return to main screen)");

        cout << endl;
        cout << endl;

        terminalModifier.printTwoColumns("OLL (o)", "PLL (p)");
        terminalModifier.printTwoColumns("Create Algorithm (c)", "Edit Algorithms (e)");

    terminalModifier.setNonBlockingInput();
    // while loop to decide between OLL/PLL practice, edit algorithm or create algorithm (last two not working rn)
    while (true) {
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
    Timer terminalModifier;
    terminalModifier.clearScreen();
    cout << "This feature doesnt work homie";
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

    if(!moo.fileInfoHolder.empty()) { // if the vector has something
        moo.fileInfoHolder.clear();
    }

    if (isOll) {
        moo.vectorFileInfo("Algorithms", "ollAlgs"); // send all of the information form the ollAlgs file to the moo vector
    } else {
        moo.vectorFileInfo("Algorithms", "pllAlgs"); // send all of the information form the pllAlgs file to the moo vector
    }

    terminalModifer.setNonBlockingInput();
reprint_w_new_values:
    // for printing
    terminalModifer.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    // casual prints
    terminalModifer.printCentered("Algorithm Navigator");
    cout << endl;
    terminalModifer.printCentered("Choose what Algorithm category you want");
    terminalModifer.printCentered("Enter to proceed, Esc to exit");
    terminalModifer.printTwoColumns("<- F", "J ->");
        
    cout << endl << endl << endl;

    // prints alg category
    terminalModifer.printCentered(moo.fileInfoHolder[navCounter]);
    algName = moo.fileInfoHolder[navCounter];


    while (true) {
        c = 0; // for std input

        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        // conditional control for loops/ending

        // if J
        if (c == 106) {
            navCounter++;
            c = 0;

            if(navCounter > moo.fileInfoHolder.size()) {
                navCounter = 0;
            }

            goto reprint_w_new_values;
        }

        // if F
        if (c == 102) {
            navCounter--;
            c = 0;

            if (navCounter < 0) {
                navCounter = moo.fileInfoHolder.size();
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
string algorithmPracticeScreens::algNavigator(const string& algName) {
    DataManager moo;
    Timer terminalModifer;
    string specificAlgName, alg, algAscii;
    char c = 0;

    vector<string> tempVec;
    tempVec.reserve(5);

    terminalModifer.setNonBlockingInput();

    if(!moo.fileInfoHolder.empty()) { // if the vector has something
        moo.fileInfoHolder.clear();
    }

    if (isOll) {
        moo.vectorFileInfo("Algorithms", "ollAlgPhotos"); // send send specific data into vector

        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            string holder = moo.fileInfoHolder[x];
            holder = holder.substr(0, holder.find(":"));
            
            if (algName == holder.substr(0, holder.length()-2)) {
                tempVec.emplace_back(moo.fileInfoHolder[x]);
            }
        }

    } else {
        moo.vectorFileInfo("Algorithms", "pllAlgPhotos"); // send send specific data into vector

        // processing for isolating the only related algorithms

        for(int x = 0; x < moo.fileInfoHolder.size(); x++) {
            if (algName.substr(0, 1) == moo.fileInfoHolder[x].substr(0,1)) {
                tempVec.emplace_back(moo.fileInfoHolder[x]);
            }
        }
    }

reprint_w_new_values:

    terminalModifer.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    if(tempVec.size() == 1) { // only if the alg category has one specific algorithm (that is just your choice)
        terminalModifer.printCentered("Algorithm Navigator");
        cout << endl;
        terminalModifer.printCentered("Press enter to view timer screen");
    } else {
        terminalModifer.printCentered("Algorithm Navigator");
        cout << endl;
        terminalModifer.printCentered("What Algorithm do you want to practice?");
        terminalModifer.printCentered("Enter to proceed, Esc to exit");
        terminalModifer.printTwoColumns("<- F", "J ->");
    }

    // create a string stream out of every data string thats pulled in, this will get split into specific name, algorithm, and ascii
    stringstream ss(tempVec[algNavCounter]);

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

        // if J
        if (c == 106) {
            algNavCounter++;
            c = 0;

            if(algNavCounter > tempVec.size()-1) {
                algNavCounter = 0;
            }

            goto reprint_w_new_values;
        }

        // if F
        if (c == 102) {
            algNavCounter--;
            c = 0;

            if (algNavCounter < 0) {
                algNavCounter = tempVec.size()-1;
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
string algorithmPracticeScreens::fromSolved(const string& algName) {
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

string algorithmPracticeScreens::splashScreen(const string& specificAlgName) {
    Timer terminalModifier;
    DataManager dataMod;
    string algType;
    fs::path fullPath;
    char c = 0;

    if(!dataMod.fileInfoHolder.empty()){ // if the vector has something
        dataMod.fileInfoHolder.clear();
    }

    if(isOll) {
        fs::path basePath = fs::absolute("Data/Algorithms/OLL");
        fs::path extension = ".txt";
        fullPath = basePath / specificAlgName += extension;
        dataMod.vectorFileInfo(fullPath);
    } else {
        fs::path basePath = fs::absolute("Data/Algorithms/PLL");
        fs::path extension = ".txt";
        fullPath = basePath / specificAlgName += extension;
        dataMod.vectorFileInfo(fullPath);
    }

refresh_the_screen:
    long long lasttime = 0;
    long long pbtime = 0;
    long long avgTime = 0;
    string formattedTime;
    string pbString = "PB: ";
    string ao5String = "Ao5: ";
    string ao12String = "Ao12: ";
    string ao100String = "Ao100: ";

    // printing specific alg and last time
    terminalModifier.clearScreen();
    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered(specificAlgName);
    cout << endl;

    lasttime = dataMod.getLatestAlgTime();
    TimeSpan lastSpan(lasttime); // this turns long long ms into a timespan .grabTime will return the time as a string
    formattedTime = lastSpan.grabTime();

    terminalModifier.printCentered(formattedTime);
    cout << endl << endl;

    // logic for PB string
    pbtime = dataMod.grabPB();
    TimeSpan pbSpan(pbtime);
    pbString += pbSpan.grabTime();

    // logic for Ao5
    avgTime = dataMod.grabAO5();
    TimeSpan ao5Span(avgTime);
    ao5String += ao5Span.grabTime();

    //logic for Ao12
    avgTime = dataMod.grabAO12();
    TimeSpan ao12Span(avgTime);
    ao12String += ao12Span.grabTime();

    //logic for Ao100
    avgTime = dataMod.grabAO100();
    TimeSpan ao100Span(avgTime);
    ao100String += ao100Span.grabTime();

    if (dataMod.fileInfoHolder.size() < 3) {
        // do nothing
    } else if (dataMod.fileInfoHolder.size() < 5) {
        terminalModifier.printCentered(pbString);
    } else if (dataMod.fileInfoHolder.size() < 12) {
        terminalModifier.printTwoColumns(pbString, ao5String);
    } else if (dataMod.fileInfoHolder.size() < 100) {
        terminalModifier.printTwoColumns(pbString, ao5String);
        cout << endl;
        terminalModifier.printCentered(ao12String);
    } else  {
        terminalModifier.printTwoColumns(pbString, ao5String);
        terminalModifier.printTwoColumns(ao12String, ao100String);
    }

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
            dataMod.undoTime(fullPath);
            goto refresh_the_screen;
        } else if (c > 0) {
            return "T";
        }

    }

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
void algorithmPracticeScreens::mainTimer(const string& specificAlgname) {
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
top:
    Timer terminalModifier;
    algorithmPracticeScreens algoPracticeSwitch;
    char c = 0;
    toggleInspectionTime = false;
    toggleOrientation = false;
    orientation = "";

    terminalModifier.clearScreen();

        cout << endl << endl << endl << endl << endl << endl;
    
        terminalModifier.printCentered("Timer Screen");
        terminalModifier.printCentered("(esc to return to main screen)");

        cout << endl;
        cout << endl;

        terminalModifier.printTwoColumns("New Session (n)", "Old Session (o)");
        terminalModifier.printCentered("Session Manager (s)");

    terminalModifier.setNonBlockingInput();
    // while loop to decide between OLL/PLL practice, edit algorithm or create algorithm (last two not working rn)
    while (true) {
        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 'n') {
            terminalModifier.restoreTerminal();
            newSession();
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 'o') {
            terminalModifier.restoreTerminal();
            previousSession(); // calls the same function as oll but the truth value is what makes the difference
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 's') {
            terminalModifier.restoreTerminal();
            sessionManager();
            terminalModifier.restoreTerminal();
            goto top;
        }  else if (c == 27) { // escape to exit
            c = 0;
            terminalModifier.restoreTerminal();
            return;
        }
    }
    terminalModifier.restoreTerminal();
}

// dynamically creates a session if the file isnt there
void timerScreen::newSession() {
    DataManager dataMan;
    Timer timer;
    Timer terminalModifier;
    string sessionName;
    string holder = "";

    sessionName = dataMan.createSessionLoop();

    while (true) {
        holder = splashScreen(sessionName);

        if (holder == "F") {
            terminalModifier.restoreTerminal();
            return;
        }

        mainTimer(sessionName);
    }
}

// opens session up
void timerScreen::previousSession() {
top:
    DataManager dataMan;
    Timer timer;
    Timer terminalModifier;
    string sessionName = "";
    string holder = "";
    char c = 0;

    terminalModifier.restoreTerminal();

    terminalModifier.clearScreen();
    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered("What session would you like to re-join? (exclude .txt)");
    dataMan.displayFolder("Sessions");

    cout << endl << endl << endl;

    getline(cin, sessionName);

    if (!dataMan.isValidFilename(sessionName) || !dataMan.fileExists(sessionName)) {
        goto top;
    }


    while (true) {
        holder = splashScreen(sessionName);

        if (holder == "F") {
            terminalModifier.restoreTerminal();
            return;
        }

        mainTimer(sessionName);
    }
}

// displays all session files - probably using data visualizer
void timerScreen::sessionManager() {
    Timer terminalModifier;
    terminalModifier.clearScreen();
    cout << "This feature doesnt work homie";
}
void timerScreen::edit() {

}
void timerScreen::del() {

}

string timerScreen::splashScreen(const string& session) {
    Timer terminalModifier;
    DataManager dataMod;
    string algType;
    
    fs::path fullPath;
    char c = 0;

    if(!dataMod.fileInfoHolder.empty()){ // if the vector has something
        dataMod.fileInfoHolder.clear();
    }

    fs::path basePath = fs::absolute("Data/Sessions");
    fs::path extension = ".txt";
    fullPath = basePath / session += extension;
    dataMod.vectorFileInfo(fullPath);

refresh_the_screen:
    // stat variables
    long long lasttime = 0;
    long long pbtime = 0;
    long long avgTime = 0;
    string formattedTime;
    string pbString = "PB: ";
    string ao5String = "Ao5: ";
    string ao12String = "Ao12: ";
    string ao100String = "Ao100: ";

    // printing specific alg and last time
    terminalModifier.clearScreen();
    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered(session);
    cout << endl;

    lasttime = dataMod.getLatestAlgTime();
    TimeSpan lastSpan(lasttime); // this turns long long ms into a timespan .grabTime will return the time as a string
    formattedTime = lastSpan.grabTime();

    terminalModifier.printCentered(formattedTime);
    cout << endl << endl;

    // logic for PB string
    pbtime = dataMod.grabPB();
    TimeSpan pbSpan(pbtime);
    pbString += pbSpan.grabTime();

    // logic for Ao5
    avgTime = dataMod.grabAO5();
    TimeSpan ao5Span(avgTime);
    ao5String += ao5Span.grabTime();

    //logic for Ao12
    avgTime = dataMod.grabAO12();
    TimeSpan ao12Span(avgTime);
    ao12String += ao12Span.grabTime();

    //logic for Ao100
    avgTime = dataMod.grabAO100();
    TimeSpan ao100Span(avgTime);
    ao100String += ao100Span.grabTime();

    if (dataMod.fileInfoHolder.size() < 3) {
        // do nothing
    } else if (dataMod.fileInfoHolder.size() < 5) {
        terminalModifier.printCentered(pbString);
    } else if (dataMod.fileInfoHolder.size() < 12) {
        terminalModifier.printTwoColumns(pbString, ao5String);
    } else if (dataMod.fileInfoHolder.size() < 100) {
        terminalModifier.printTwoColumns(pbString, ao5String);
        cout << endl;
        terminalModifier.printCentered(ao12String);
    } else  {
        terminalModifier.printTwoColumns(pbString, ao5String);
        terminalModifier.printTwoColumns(ao12String, ao100String);
    }

    cout << endl << endl;

    terminalModifier.printCentered("Press any button to start the timer");
    terminalModifier.printCentered("u to undo last solve");
    terminalModifier.printCentered("Esc to go back");

    cout << "Inspection Time (i): " << boolalpha << toggleInspectionTime << endl; // boolapha makes it print true/false
    
    if (orientation.length() != 0) {
        cout << "Set Solve Orientation (s): " << "Front " << oriental.frontOrientation << " Top " << oriental.topOrientation  << endl;
    } else {
        cout << "Set Solve Orientation (s)" << endl;
    }
    

    terminalModifier.setNonBlockingInput(); // sets raw mode

    while (true) {
        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 27) {
            terminalModifier.restoreTerminal();
            return "F"; // escape to menu
        }  else if (c == 117) { // undo button
            dataMod.undoTime(fullPath);
            goto refresh_the_screen;
        }  else if (c == 'i') {
            inspectionToggle();
            goto refresh_the_screen;
        } else if (c == 's') {
            terminalModifier.restoreTerminal();

            if (toggleOrientation == true) {
                orientation.clear();
            } else {
                oriental.setOrientation();
                orientation = oriental.getOrientation();
                terminalModifier.clearScreen();
            }

            orientationToggle();
            goto refresh_the_screen;
        } else if (c > 0) {
            terminalModifier.restoreTerminal(); // idk where this bug is
            return "T";
        }

    }

}

void timerScreen::mainTimer(const string& session) {
    string algType;
    Timer timer;
    Timer terminalModifier;
    DataManager mooski;
    Scramble scrambler_and_orientation;
    time_t timestamp = time(NULL);
    struct tm datetime = *localtime(&timestamp);
    char date[50];
    string orientation;
    string scramble;

    long long finalTime;

    scrambler_and_orientation.newScramble();
    scramble = scrambler_and_orientation.getScramble();

    terminalModifier.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    terminalModifier.printCentered("Here is your scramble: ");

    if (toggleInspectionTime == true) {
        terminalModifier.printCentered("Any button to proceed into inspection");
    } else {
        terminalModifier.printCentered("Any button to proceed into timer");
    }
    
    cout << endl;
    terminalModifier.printCentered(scramble);

    char c = 0;
    
    terminalModifier.setNonBlockingInput();
    while (true) {
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        
        if (c > 0) {
            c = 0;
            break;
        }
    }
    terminalModifier.restoreTerminal();

    if (toggleInspectionTime == true) {
        timer.inspectionTime();
    }

    if (timer.inspectionLimitReached == true) { // false by default
        return;
    }

    timer.runTimer();

    finalTime = timer.returnFinalTime();

    strftime(date, 50, "%m/%d/%y", &datetime);

    if (toggleOrientation) {
        mooski.saveSolveOrientation(session, finalTime, scramble, orientation, date);
    } else {
        mooski.saveSolveNoOrientation(session, finalTime, scramble, date);
    }
}

void timerScreen::inspectionToggle() {
    if (toggleInspectionTime == true) {
        toggleInspectionTime = false;
    } else {
        toggleInspectionTime = true;
    }

}

void timerScreen::orientationToggle() {
    if (toggleOrientation == true) {
        toggleOrientation = false;
    } else {
        toggleOrientation = true;
    }
}
