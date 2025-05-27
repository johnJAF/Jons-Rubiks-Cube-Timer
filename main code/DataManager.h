#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include <vector>
#include <filesystem>
#include <regex>
#include <limits>

using namespace std;
namespace fs = std::filesystem;

// class to manage the data of any given function. Abstracted enough to be used universally
class DataManager {
    string sessionName;
    string algName;
    // if not editing mode we are in deleting mode
    bool editingMode; 

public:
    vector<string> fileInfoHolder;
    // file navigation
    bool createFile(const string& whatFolder, const string& fileName); // creates a session or an algorithm
    string createSessionLoop();
    bool isValidFilename(const string& name);
    bool fileExists(const string& session);
    bool deleteFile(const string& whatFolder, const string& whatFile); // deletes a file or session
    void displayFolder(const string& whatFolder); // prints the feature folder
    void vectorFileInfo(const string& whatFolder, const string& whatFile); // grabs all file info as a dynamic vector and stores it
    void vectorFileInfo(const fs::path& pathy);

    // going to save time, in order of miliseconds, orientaiton, date. The session argument is just for where its supposed to go
    bool saveSolveNoOrientation(const string& session, const long long milliseconds, const string& scramble, const string& date);
    bool saveSolveOrientation(const string& session, const long long milliseconds, const string& scramble, const string& orientation, const string& date);

//     // getters 
//     string getSessionName(); // returns current session file name
//     string getSolveName(); // returns current algorithm file name
//     string getSolve(int index); // returns all solve information
//     string getAlgCategory(string ollOrPll, int index);
//     string displayAlgPhoto(string ollOrPll, string algorithm);


//     // for the algorithmPractice class
//     void writeAlgorithm();
//     void drawAlgorithm(); 
    bool saveAlgTime(const string& ollpll, const string& specificAlgName, const long long milliseconds, const char[50]);
    long long getLatestAlgTime();
    void undoTime(const fs::path& fullPath);
    int createID();

    // for averaging
    long long grabAO5(); // returns miliseconds
    long long grabAO12();
    long long grabAO100();

    long long grabPB(); // returns lowest time
};