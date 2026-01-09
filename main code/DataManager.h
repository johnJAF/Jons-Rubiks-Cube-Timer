#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <random>
#include <filesystem>
#include <regex>
#include <limits>

#include "Scramble.h"

using namespace std;
namespace fs = std::filesystem;

// class to manage the data of any given function. Abstracted enough to be used universally
class DataManager {
    string sessionName;
    string algName;
    // if not editing mode we are in deleting mode
    bool editingMode; 
    unsigned seed;
    using Clock = std::chrono::steady_clock;

public:
    vector<string> fileInfoHolder;
    // file navigation
    bool createFile(const string& whatFolder, const string& fileName); // creates a session or an algorithm
    string createSessionLoop();
    bool isValidFilename(const string& name);
    bool fileExists(const string& session, const string& ollpll);
    bool deleteID(const fs::path& keysPath, int index, const string& ollpll);
    void displayFolder(const string& whatFolder); // prints the feature folder
    void displaySessionFile(const fs::path& whatFile);
    void displayAlgorithmFile(const fs::path& whatFile);
    void vectorFileInfo(const string& whatFolder, const string& whatFile); // grabs all file info as a dynamic vector and stores it
    void vectorFileInfo(const fs::path& pathy);

    // going to save time, in order of miliseconds, orientaiton, date. The session argument is just for where its supposed to go
    bool saveSolveNoOrientation(const string& session, const long long milliseconds, const string& scramble, const string& date);
    bool saveSolveOrientation(const string& session, const long long milliseconds, const string& scramble, const string& orientation, const string& date);
    bool saveSolveWithAllData(const string& session, string& version, int id, const long long milliseconds, const string& scramble, const string& orientation, const string& date);

//     // for the algorithmPractice class
//     void writeAlgorithm();
//     void drawAlgorithm(); 
    bool saveAlgTime(const string& ollpll, const string& specificAlgName, const long long milliseconds, const char[50]);
    long long getLatestAlgTime();
    void undoTime(const fs::path& fullPath);
    int createSessionID(const string& session); // will be implemented in saveSolveOrentations and saveAlgTime soon
    int createAlgID(const string& ollpll, const string& specificAlgName);

    // for averaging
    long long grabAO5(); // returns miliseconds
    long long grabAO12();
    long long grabAO100();

    long long grabPB(); // returns lowest time
};