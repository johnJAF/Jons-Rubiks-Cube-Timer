#include "UserFlow.h"


int main() {
    // dont worry about this
    string stopProgram = "";
    Timer meow;
    Scramble algorithm; 

    // all screen objects
    introScreens introSwitch;
    scrambleScreen scrambleSwitch;
    algorithmPracticeScreens algoPracticeSwitch;
    dataVisualizerScreen dataVisSwitch;
    timerScreen timeSwitch;

    // this runs the intro screen screens and returns the character of the app feature chosen
    char optionChosen = introSwitch.startScreen();
    
    // depending on the feature chosen, we're gonna run that feature.
    if (optionChosen == 's') {
        scrambleSwitch.mainScreen();
    } else if (optionChosen == 'a'){
        algoPracticeSwitch.mainScreen();
    } else if (optionChosen == 'd') {
        dataVisSwitch.mainScreen();
    } else if (optionChosen == 't') {
        timeSwitch.mainScreen();
    }


    // while (true) {
    //     cout << "Enter q to quit, to enter the timer, enter anything on the keyboard: ";

    //     getline(cin, stopProgram);

    //     if (stopProgram == "q") {
    //         break;
    //     }

    //     meow.runTimer();
    // }

    // algorithm.newScramble();
    // algorithm.print();
    // algorithm.newScramble();
    // algorithm.print();
    // algorithm.newScramble();
    // algorithm.print();
    
    // algorithm.setScramble();

    // algorithm.setOrientation();
    // algorithm.print();
    // cout << algorithm.getOrientation();

    return 0;
}