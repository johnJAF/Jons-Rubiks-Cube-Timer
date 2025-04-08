#include "UserFlow.h"

////////////////////////////////////////////////////////
//////////////  MEOW intro screens MEOW  ///////////////
////////////////////////////////////////////////////////

// first screen user sees "Press any button to continue"
void introScreens::startScreen() {

}

// second screen user sees, shows all four options between scrambler, timer, datavisualizer, alogirthmpractice
void introScreens::mainScreen() {

}

// logic to choose between the four options
void introScreens::chooseOption() {

}

////////////////////////////////////////////////////////
//////////////  MEOW scramble screen MEOW  /////////////
////////////////////////////////////////////////////////

// scramble screen main scren
void scrambleScreen::mainScreen() {

}

////////////////////////////////////////////////////////
//////////////  MEOW algoPractice MEOW  ////////////////
////////////////////////////////////////////////////////

void algorithmPracticeScreens::mainScreen() {

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