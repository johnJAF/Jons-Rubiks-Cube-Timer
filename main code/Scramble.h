#pragma once

#include <iostream>
#include <string>
#include <array>
#include <random>
#include <chrono>
#include <sstream>
#include <vector>

using namespace std;

class Scramble {
    array<string, 20> scrambled; // 20 moves long - R2 or U2 type of moves counted as one move
    // b = blue, g = green, y = yellow, w = white, r = red, o = orange.
    using Clock = std::chrono::steady_clock; // just to grab time right now for random
    unsigned seed;

    static const array<std::string, 3> rightSide;
    static const array<std::string, 3> leftSide;
    static const array<std::string, 3> face;
    static const array<std::string, 3> up;
    static const array<std::string, 3> down;
    static const array<std::string, 3> back;
    
    static const array<std::array<std::string, 3>, 6> twoDeeList;

public:
    char frontOrientation;
    char topOrientation;
    
    void newScramble(); // random scramble using current time
    string getScramble();

    void setScramble(); // set to a specific scramble
    bool checkScrambleIssues(const array<string, 20>& scramblington);

    // this is to set the orientation for the sake of the scramble, just show how you held it.
    void setOrientation(); // sets both front and top orientation
    void setOrientation(const string& presetOrientation);

    string getOrientation(); // returns string for front, then top

    void print();
};