#pragma once

#include "Timer.h"
#include "Scramble.h"
#include <string>
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
    string algorithmBeingUsed;


public:
    void mainScreen();
    void chooseOption();
        void oll();
        void pll();
        void own();
        void editAlgs(); // probably has an object that extends datavisualizer which allows for display, and editation

    // this navigator screen will be used 4 times in choosing what name of algorithm/photo of algorithm for OLL/PLL
    // uses isOLL
     void navigator();

    // pulls from dataset that checks what algorithm you're doing
    // uses isOll
    void fromSolved();

    // just in case while you were solving you made some mistake and you want to remove the very last solve instance.
    void undoSolve();

    // own
    void algorithmName();
    void typeInAlgMoves();
    void drawMap(); // displays map that user inputs alg into

    // creates a timer instance based on algorithm chosen, saves it to that respective file
    // different baesd on isOll. Uses data vizualizer object code to show PB, Ao5, Ao12.
    void mainTimer(); 

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
public:
    void mainScreen();

    void newSession(); // dynamically creates a session if the file isnt there
    void previousSession(); // opens session up
    void sessionManager(); // displays all session files - probably using data visualizer   
        void edit();
        void del();
    
    void mainTimer();
        void undo();
};
