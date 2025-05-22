#pragma once

#include "Timer.h"
#include "Scramble.h"

#include <string>
#include <sstream>
#include <iomanip>

class introScreens {
public:
    // first screen user sees "Press any button to continue"
    void startScreen();

    // second screen user sees, shows all four options between scrambler, timer, datavisualizer, alogirthmpractice
    void mainScreen(char moo);
};

class scrambleScreen {
public:
    void mainScreen(); // one and only screen
};

class algorithmPracticeScreens {
    bool isOll;
    string actualAlgorithm;

public:
    void mainScreen();
        void opll();
        void own();
        void editAlgs(); // probably has an object that extends datavisualizer which allows for display, and editation

    // this navigator screen will be used 4 times in choosing what name of algorithm/photo of algorithm for OLL/PLL
    // uses isOLL
    string navigator(); // navigates through list of alg names
    string algNavigator(string file); // navigates thorugh list of alg photos

    // pulls from dataset that checks what algorithm you're doing
    // uses isOll
    string fromSolved(string file);

    string splashScreen(string justInCase);

    // just in case while you were solving you made some mistake and you want to remove the very last solve instance.
    void undoSolve();

    // own
    void algorithmName();
    void typeInAlgMoves();
    void drawMap(); // displays map that user inputs alg into

    // creates a timer instance based on algorithm chosen, saves it to that respective file
    // different baesd on isOll. Uses data vizualizer object code to show PB, Ao5, Ao12.
    void mainTimer(string file); 

};

class dataVisualizerScreen {
public:
    void mainScreen();

    void fileDisplay();

    void fileSearch();

    void fileCheck();

    // this might have to run some python scripts that can display all of the file data chosen.
    void displayData();

};


class timerScreen {
    bool toggleOrientation;
    bool toggleInspectionTime;

public:
    void mainScreen();

    void newSession(); // dynamically creates a session if the file isnt there
    void previousSession(); // opens session up
    void sessionManager(); // displays all session files - probably using data visualizer   
        void edit();
        void del();
    
    void mainTimer(string session);
        void inspectionToggle();
        bool getInspectionToggle();
        void orientationToggle();
        bool getOrientationToggle();
};
