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
top:
    DataManager dataMan;
    Timer timer;
    Timer terminalModifier;
    string sessionName;
    string holder = "";

    sessionName = dataMan.createSessionLoop();

    if (sessionName == "") {
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

// opens session up
void timerScreen::previousSession() {
top:
    DataManager dataMan;
    fs::path folderpath = "Data/Sessions";
    Timer timer;
    Timer terminalModifier;
    string sessionName = "";
    string holder = "";
    char c = 0;

    terminalModifier.restoreTerminal();

    terminalModifier.clearScreen();

    int counter = 0; // counter for how many files there are (if its only 1 (a gitkeep)) then it should return
    for (const auto& session : fs::directory_iterator(folderpath)) { // for every session in the sessions folder
        counter++;
    }
    if (counter <= 1) {
        cerr << endl << "You cant open a previous session if there are no previous sessions." << endl;
        return;
    }

    cout << endl << endl << endl << endl << endl << endl;
    terminalModifier.printCentered("What session would you like to re-join?");
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

// allows you to edit or delete sessions
void timerScreen::sessionManager() {
top:
    Timer terminalModifier;
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

        terminalModifier.printTwoColumns("Delete a Session (d)", "Edit a Session (e)");

    terminalModifier.setNonBlockingInput();
    // while loop to decide between OLL/PLL practice, edit algorithm or create algorithm (last two not working rn)
    while (true) {
        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 'd') {
            terminalModifier.restoreTerminal();
            del();
            terminalModifier.restoreTerminal();
            goto top;
        } else if (c == 'e') {
            terminalModifier.restoreTerminal();
            edit(); // calls the same function as oll but the truth value is what makes the difference
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

// displays all session files and allows you to pick one
fs::path timerScreen::displayAndChoose(bool areYouDeleting) {
top:
    DataManager dataMan;
    fs::path folderpath = "Data/Sessions/";
    Timer timer;
    Timer terminalModifier;
    string sessionName = "";
    string holder = "";
    char c = 0;

    terminalModifier.restoreTerminal();

    terminalModifier.clearScreen();

    int counter = 0; // counter for how many files there are (if its only 1 (a gitkeep)) then it should return
    for (const auto& session : fs::directory_iterator(folderpath)) { // for every session in the sessions folder
        counter++;
    }
    if (counter <= 1) {
        cerr << endl << "You cant open a previous session if there are no previous sessions." << endl;
        return "";
    }

    cout << endl << endl << endl << endl << endl << endl;
    if (areYouDeleting) {
        terminalModifier.printCentered("What session would you like to delete? (-1 to exit)");
        terminalModifier.printCentered("(Be careful as you cannot undo this)");
    } else {
        terminalModifier.printCentered("What session would you like to edit? (-1 to exit)");
    }
    dataMan.displayFolder("Sessions");

    cout << endl << endl << endl;

    getline(cin, sessionName);

    if (sessionName == "-1") {
        return "";
    }

    if (!dataMan.isValidFilename(sessionName) || !dataMan.fileExists(sessionName)) {
        goto top;
    }

    folderpath += sessionName + ".txt";
    
    return folderpath;
}

// this returns the ID and the index of the ID IN THAT ORDER
tuple<int, int> timerScreen::displayAndChooseSessionData(const fs::path& mainPath, const fs::path& keysPath) {
    fs::path chosenPath = mainPath;
    Timer terminalModifier;

    DataManager dataMan;

    terminalModifier.printCentered("Type in the session that you want to edit (-1 to exit)");
    cout << endl << endl << endl;

    dataMan.displaySessionFile(chosenPath);

    cout << endl;

    // here were gonna ask the user for an ID and basically strip for everything and then verify with the respective KEYS file
    string IDread = "";
    int intKeyChosen = 0;
    int indexCounter = 0;
    bool didItWork = true;
    while (true) {
        indexCounter = 0;
        string IDread = "";
        int intKeyChosen = 0;
        getline(cin, IDread);

        didItWork = regex_match(IDread, regex("^-?[0-9]+$")); // check only for numerical inputs

        if (IDread.length() > 7) {
            IDread = "";
            intKeyChosen = 0;
            cerr << endl << "[Error] Invalid session ID. Inappropriate ID length" << endl;
            continue;
        }

        if (!didItWork) {
            IDread = "";
            intKeyChosen = 0;
            cerr << endl << "[Error] Invalid session ID. Only use numbers." << endl;
            continue;
        }

        intKeyChosen = stoi(IDread);

        if (intKeyChosen == -1) {
            indexCounter = -1;
            break;
        }

        dataMan.fileInfoHolder.clear();
        // if the ID is validly typed, then we can check it with existing IDs (_keys.txt file)
        dataMan.vectorFileInfo("Sessions", keysPath.string());

        bool idExists = false;

        for (string data : dataMan.fileInfoHolder) { // for every id in the keys file
            indexCounter++;
            int knownKey = stoi(data);

            if (knownKey == intKeyChosen) { // if the ID we have matches with one of the IDS 
                idExists = true;
                break;
            } 
        }

        if (!idExists) {
            cerr << endl << "[Error] Invalid session ID. This ID doesnt exist" << endl;
            continue;
        }

        break;
    }

    tuple<int, int> tuplington(intKeyChosen, indexCounter);

    return tuplington;
}

void timerScreen::edit() {
    DataManager dataMan;
    fs::path chosenPath;
    Timer terminalModifier;
    char c = 0;
    string line;
    string version;
    string id;
    string time;
    string scramble;
    string orientation; // depends on the type of session option
    string date;

    chosenPath = displayAndChoose(false); // should be returning a full path to a base .txt file

    // grabbing the filename and then adding _KEYS.txt to it for access to keys
    fs::path keysPath = chosenPath.stem();
    keysPath += "_KEYS";

    terminalModifier.clearScreen();

    if(chosenPath == "") {
        return;
    }

    // tuple that contains the ID wanted and the index where its at
    tuple<int, int> idAndIndex(0, 0);
    idAndIndex = displayAndChooseSessionData(chosenPath, keysPath);

    if (get<1>(idAndIndex) == -1) {
        edit();
    }

    // now that we have the exact key for what time we want to mess with, lets actually edit the time using the index we got from the chosen data
    dataMan.vectorFileInfo(chosenPath);

    string vectorLine = "";

    vectorLine = dataMan.fileInfoHolder[get<1>(idAndIndex)-1]; // use the index we got from the IDS file to match with the actual file

    // separating the data that we get form the fileInfoHoler
    stringstream baka(vectorLine);

    getline(baka, version, ':');
    getline(baka, id, ':');
    getline(baka, time, ':');
    getline(baka, scramble, ':');

    if (version == "V2") {
        getline(baka, orientation, ':');
    }

    getline(baka, date, ':');

reprint:
    terminalModifier.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    terminalModifier.printCentered("You are using this time data. What would you like to change?");
    cout << endl << endl;
    cout << "ID: " << id << endl;
    cout << "\t- Time (ms): " << time << endl;
    cout << "\t- Scramble: " << scramble << endl;

    if (version == "V2") {
        cout << "\t- Orientation: " << orientation << endl;
    }

    cout << "\t- Date: " << date << endl;

    cout << endl << endl;
    terminalModifier.printTwoColumns("Time (t)", "Scramble (s)");
    if (version == "V2") {
        terminalModifier.printTwoColumns("Orientation (o)", "Date (d)");
    }
    terminalModifier.printCentered("Date (d)");
    cout << endl;
    terminalModifier.printCentered("Delete time (-)");

    terminalModifier.setNonBlockingInput();
    
    string chosenString = ""; // this is for the stupid text display after this but it gets decided here
    while (true) {
        c = 0;
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);

        if (c == 't') {
            terminalModifier.restoreTerminal();
            chosenString = "Time";
            break;
        } else if (c == 's') {
            terminalModifier.restoreTerminal();
            chosenString = "Scramble";
            break;
        } else if (c == 'o') {
            terminalModifier.restoreTerminal();
            chosenString = "Orientation";
            break;
        } else if (c == 'd') {
            terminalModifier.restoreTerminal();
            chosenString = "Date";
            break;
        } else if (c == '-') {
            // we have vectored the file info at this point so we can just delete 

            dataMan.fileInfoHolder.erase(dataMan.fileInfoHolder.begin() + get<1>(idAndIndex)-1);

            // rewrite the vectored data into the actual file
            ofstream of(chosenPath, ios::trunc);  // trunc clears the file
            for (const string& s : dataMan.fileInfoHolder) {
                of << s << '\n';
            }

            of.close();

            // helper function because Im not trying to make this one 30 times larger (to get rid of the same ID in the _KEYS file)
            dataMan.deleteID(keysPath, get<1>(idAndIndex)-1);

            return;
        } else if (c == 27) {
            c = 0;
            return;
        } 
    }

    terminalModifier.clearScreen();

    cout << endl << endl << endl << endl << endl << endl;

    // this is going to display the text in this format (e.g):
    /**
     * 
     * (centered) Enter the new Time you'd like to use 
     * 
     *  id:
     * 
     *      - Time: Data(highlighted)
     *      - Scramble
     *      - Orientaiton
     *      - Date
     * 
     *  Enter new Time
     * 
     **/

while(true) {
        terminalModifier.printCentered("Enter the " + chosenString + " you'd like to use");
        cout << endl << endl;
        cout << "ID: " << id << endl;

        if (c == 't') {
            cout << "\t\033[1;37;44m- Time (ms)\033[0m: " << time << endl;
            cout << "\t- Scramble: " << scramble << endl;

            if (version == "V2") {
                cout << "\t- Orientation: " << orientation << endl;
            }

            cout << "\t- Date: " << date << endl;

        } else if (c == 's') {
            cout << "\t- Time (ms): " << time << endl;
            cout << "\t\033[1;37;44m- Scramble\033[0m: " << scramble << endl;

            if (version == "V2") {
                cout << "\t- Orientation: " << orientation << endl;
            }

            cout << "\t- Date: " << date << endl;

        } else if (c == 'o') {
            cout << "\t- Time (ms): " << time << endl;
            cout << "\t- Scramble: " << scramble << endl;

            if (version == "V2") {
                cout << "\t\033[1;37;44m- Orientation\033[0m: " << orientation << endl;
            }

            cout << "\t- Date: " << date << endl;
        } else if (c == 'd') {
            cout << "\t- Time (ms): " << time << endl;
            cout << "\t- Scramble: " << scramble << endl;

            if (version == "V2") {
                cout << "\t- Orientation: " << orientation << endl;
            }

            cout << "\t\033[1;37;44m- Date\033[0m: " << date << endl;
        }

        cout << endl << endl;

        string userInput = "";

    // at this point we know that we still have the vector full of times from the actual file inside of dataman. SO, if we just apply the changes to 
    // the string stream then we can just throw it back into the vector using the index we stored.
        getline(cin, userInput);

        if (userInput == "-1"){
            return;
        }

        if (regex_match(userInput, regex("^[A-Za-z0-9/'/]+$"))) {
            if (c == 't') {
            time = userInput;
            } else if (c == 's') {
                scramble = userInput;
            } else if (c == 'o') {
                orientation = userInput;
            } else if (c == 'd') {
                date = userInput;
            }
            break;
        } else {
            cerr << endl << "Invalid Input" << endl;
            continue;
        }
    }
    
    // time to validate that you entered an actual time lol
    long long longTime = 0;
    int intID = 0;
    try {
        int longTime = stoi(time);

        if (longTime < 1) {
            throw invalid_argument("");
        }
    } catch (const invalid_argument& e) {
        cerr << "Invalid input: not a number." << endl;
        goto reprint;
    } catch (const out_of_range& e) {
        cerr << "Input is out of range for a long long." << endl;
        goto reprint;
    }
    
    // rebuilding the stupid stirng
    string meow = "";
    if (version == "V2") {
        meow += version + ":" + id + ":" + time + ":" + scramble + ":" + orientation + ":" + date;
    } else if (version == "V1") {
        meow += version + ":" + id + ":" + time + ":" + scramble + ":" + date;
    }
    
    dataMan.fileInfoHolder[get<1>(idAndIndex)-1] = meow;

    // throwing the new data into the file
    ofstream of(chosenPath, ios::trunc);  // trunc clears the file
    for (const string& s : dataMan.fileInfoHolder) {
        of << s << '\n';
    }

    of.close();

    // now that the edit is made ill send the user back to reprint so that they could see the chagnes they made
    goto reprint;
}

void timerScreen::del() {
    fs::path chosenPath;
    Timer terminalModifier;
    char c = 0;

    chosenPath = displayAndChoose(true); // should be returning a full path to a base .txt file

    // grabbing the filename and then adding _KEYS.txt to it for access to keys
    fs::path keysPath = "Data/Sessions" / chosenPath.stem() += "_KEYS.txt";

    terminalModifier.clearScreen();

    if(chosenPath == "") {
        return;
    }

    // now that we have the exact session, lets dump it
    if (fs::exists(chosenPath)) {
        fs::remove(chosenPath); // deletes the file
    }
    
    // and the keys file too
    if (fs::exists(keysPath)) {
        fs::remove(keysPath); // deletes the file
    }
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
            fs::path fullpathNoExtension = basePath / session;
            dataMod.undoTime(fullpathNoExtension);
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
