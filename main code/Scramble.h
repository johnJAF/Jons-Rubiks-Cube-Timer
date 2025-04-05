#pragma once

#include <iostream>
#include <string>
#include <array>

using namespace std;

class Scramble {
    string scrambled; // 20 moves long - R2 or U2 type of moves counted as one move
    // b = blue, g = green, y = yellow, w = white, r = red, o = orange.
    char frontOrientation;
    char topOrientation;

public:
    void newScramble(); // random scramble using current time
    string getScramble();

    void setScramble(); // set to a specific scramble

    // this is to set the orientation for the sake of the scramble, just show how you held it.
    void setOrientation(); // sets both front and top orientation
    string getOrientation(); // returns string for front, then top
};