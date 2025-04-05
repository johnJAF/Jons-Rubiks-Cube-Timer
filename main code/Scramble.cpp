#include "Scramble.h"

// arrays of submoves
array<string, 3> rightSide = {"R", "R'", "R2"};
array<string, 3> leftSide =  {"L", "L'", "L2"};
array<string, 3> face =  {"F", "F'", "F2"};
array<string, 3> up =    {"U", "U'", "U2"};
array<string, 3> down =  {"D", "D'", "D2"};
array<string, 3> back =  {"B", "B'", "B2"};

// dictionary of all of the main moves
array<array<string, 3>, 6> twoDeeList = {rightSide, leftSide, face, up, down, back};

// random scramble using random at current time (20 positions)
void Scramble::newScramble() {
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

array<string, 20> Scramble::getScramble() {
    return scrambled;
}

// to trim strings
string trim(const std::string& str) {
    size_t first = str.find_first_not_of(' ');
    if (first == std::string::npos) return ""; // all spaces!

    size_t last = str.find_last_not_of(' ');
    return str.substr(first, last - first + 1);
}

// set to a specific scramble
void Scramble::setScramble() {
    bool spaceDelimiter = false;
    string choice = "";
    string trimmed = "";
    array<string, 20> newListOfPositions;
    
    while (true) {
        cout << "THIS FUNCTION ONLY WORKS IF YOUR SCRAMBLE IS LESS THAN 20 MOVES" << endl;
        cout << "IF YOUR SCRAMBLE WAS SHORTER THAN 20 USE X's TO SHOW BLANK" << endl;
        cout << "Would you like to type in the whole algorithm (spaces) or use new lines (new)? '-1' to leave ";
        cin >> choice;

        trimmed = trim(choice);

        if(trimmed == "-1") {
            cout << endl;
            cout << "You exited Set Scramble Mode";
            cout << endl;
            break;
        } else if (trimmed == "spaces") {
            string temp = "";
            vector<std::string> moves;
            string move;

            cout << endl << "Make sure you separate all of the scramble positions with spaces eg. F2 R L' R' D" << endl;

            cin.ignore(); // Clear leftover newline from previous cin
            getline(cin, temp);
            temp = trim(temp);

            istringstream iss(temp);

            while (iss >> move) {
            moves.push_back(move);
            }
            
            // this just makes sure that only 20 inputs from the console go into the scramble
            size_t copySize = std::min(moves.size(), newListOfPositions.size());
            copy(moves.begin(), moves.begin() + copySize, newListOfPositions.begin());

            if (checkScrambleIssues(newListOfPositions)) {
                continue;
            }

        } else if (trimmed == "new") {
            string temp = "";
            for(int x = 0; x < 20; x++) {
                cin >> temp;
                newListOfPositions[x] = temp;
            }
            if (checkScrambleIssues(newListOfPositions)) {
                continue;
            }
        } else {
            cout << "Please choose one of the options.";
            continue;
        }
    }

    scrambled = newListOfPositions;
}

bool Scramble::checkScrambleIssues(array<string, 20> scramblington) {
    for(int x = 0; x < scramblington.size(); x++) {
        if(scramblington[x] == "X" || scramblington[x] == "x") {
            continue;
        }

        string moveLetter = scramblington[x].substr(0, 1);
        if (moveLetter != "F" && moveLetter != "R" && moveLetter != "L" &&
        moveLetter != "U" && moveLetter != "D" && moveLetter != "B") {
            cout << "You did not input the scramble correctly" << endl << "Make sure you are not including unnecessary spaces or fake letters" << endl;
            return false;
        }
    }

    return true;
}

// this is to set the orientation for the sake of the scramble, just show how you held it.
void Scramble::setOrientation() { // for top and front in that order

}

// returns top the front as string
string Scramble::getOrientation() {

}

