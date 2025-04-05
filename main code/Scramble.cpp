#include "Scramble.h"

// random scramble using random at current time (20 positions)
void Scramble::newScramble() {
    // arrays of submoves
    array<string, 3> right = {"R", "R'", "R2"};
    array<string, 3> left =  {"L", "L'", "L2"};
    array<string, 3> face =  {"F", "F'", "F2"};
    array<string, 3> up =    {"U", "U'", "U2"};
    array<string, 3> down =  {"D", "D'", "D2"};
    array<string, 3> back =  {"B", "B'", "B2"};

    // dictionary of all of the main moves
    array<array<string, 3>, 6> twoDeeList = {right, left, face, up, down, back};

    // random number processing
    seed = std::chrono::system_clock::now().time_since_epoch().count();
    mt19937 generator(seed); // seed based on time
    uniform_int_distribution<int> distribution(0, 5); // seed to pick main moves
    uniform_int_distribution<int> distribution2(0, 2); // random to pick submoves

    int moveIndex = distribution(generator);
    int subMoveIndex = distribution2(generator);

    scrambled[0] = twoDeeList[moveIndex][subMoveIndex];

    // runs 20 times for scramble
    for (int x = 1; x < 20; x++) {
    redo_choice:
        int moveIndex = distribution(generator);
        int subMoveIndex = distribution2(generator);

        // if the current submoves first letter (which tells the main move category) is the same as the last one, re-generate a new group to go to.
        if(scrambled[x-1].substr(0, 1) == twoDeeList[moveIndex][subMoveIndex].substr(0,1)) {
            goto redo_choice; // this repetition should avoid inverses, or duplicates by re-randomizing
        }

        scrambled[x] = twoDeeList[moveIndex][subMoveIndex];
    }
}

string Scramble::getScramble() {

}

// set to a specific scramble
void Scramble::setScramble() {

}

// this is to set the orientation for the sake of the scramble, just show how you held it.
void Scramble::setOrientation() { // for top and front in that order

}

// returns top the front as string
string Scramble::getOrientation() {

}

