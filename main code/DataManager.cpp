#include "DataManager.h"
namespace fs = std::filesystem;

// file navigation 
// creates a session or an algorithm
// whatFolder can be Algorithms or TimerSessions 
// returns true if created, false if already exists. Implemented by programmer
bool DataManager::createFile(string whatFolder, string fileName) {
    // path connection without concatonation because this is safer
    fs::path basePath = fs::absolute("Data/" + whatFolder);
    fs::path extension = ".txt";
    fs::path fullPath = basePath / fileName += extension;

    // makes sure that they are no /, \, goofy symbols, using the isValidFileNameFunction
    if (!isValidFilename(fileName)) {
        cerr << endl << "[Error] Invalid file name. Use only letters, numbers, -, _." << endl;
        return false; // program escape to say name wasnt good
    }

    // uses weakly_canonical to follow symb links and and ../, in case it was somehow snuck in still.
    fs::path normalized = fs::weakly_canonical(fullPath);
    if (normalized.string().rfind(basePath.string(), 0) != 0) {
        cerr << endl << "[Error] Unauthorized path access attempt." << endl;
        return false;
    }

    // if the path already exists, its gonna print an error and send you back
    if (fs::exists(fullPath)) {
        cout << endl << "[Notice] File already exists. Choose another name." << endl;
        return false;
    }

    // creates the file at the given path, if something was wrong with the file creation itll throw an error.
    ofstream meow(fullPath);
    if (!meow) {
        cerr << endl << "[Error] Failed to create file: " << fullPath << endl;
        return false;
    }

    cout << endl << "[Success] File created: " << fullPath << endl;
    return true;
}

// ran to check if the sesion name that is inputted is not trying to go through the file directory
bool DataManager::isValidFilename(const string& name) {
    // Only letters, numbers, underscores, and dashes
    return regex_match(name, regex("^[A-Za-z0-9_-]+$"));
}

// only for the timerScren, user input for session name
void DataManager::createSessionLoop() {
    string file = "";
    bool didItWork = false;

    while (!didItWork) {
        cout << endl << "What do you want to name this session? ";
        getline(cin, file);  // safer than `cin >> file` because it captures full line input

        didItWork = createFile("Sessions", file);
    }
}

// deletes a file or session
void DataManager::deleteFile(string whatFolder, string whatFile) {

}

// prints the feature folder
void DataManager::displayFolder(string whatFolder) {

}

// grabs all file info as a dynamic vector and stores it
void DataManager::returnFileInfo(string whatFile) {
    
}

// verification for file existance when you type it in
bool DataManager::fileIsThere(string whatFolder, string whatFile) {

}

// going to save time, in order of miliseconds, orientaiton, date. The session argument is just for where its supposed to go
void DataManager::saveSolveNoOrientation(string session, long long milliseconds, string date) {

}

void DataManager::saveSolveOrientation(string session, long long milliseconds, string orientation, string date) {

}


// getters 
// returns current session file name
string DataManager::getSessionName() {

}

// returns current algorithm file name
string DataManager::getSolveName() {

}

// returns all solve information
string DataManager::getSolve(int index) {

}

string DataManager::getAlgCategory(string ollOrPll, int index) {

}

string DataManager::displayAlgPhoto(string ollOrPll, string algorithm) {

}


// for the algorithmPractice class
void DataManager::writeAlgorithm() {

}

void DataManager::drawAlgorithm() {

}


// for averaging
// returns miliseconds
long long DataManager::grabAO5() {

}

long long DataManager::grabAO12() {

}

// returns lowest time
long long DataManager::grabPB() {
    
}