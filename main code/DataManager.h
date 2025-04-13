#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <filesystem>

namespace fs = std::filesystem;

using namespace std;

// class to manage the data of any given function. Abstracted enough to be used universally
class DataManager {
    string sessionName;
    string algName;
    vector<string> fileInfoHolder;

public:
    void createDataDirectories();
    // file navigation
    void createFile(string whatFolder, string fileName); // creates a session or an algorithm
    void deleteFile(string whatFolder, string whatFile); // deletes a file or session
    void displayFolder(string whatFolder); // prints the feature folder
    void returnFileInfo(string whatFile); // grabs all file info as a dynamic vector and stores it

    // verification for file existance when you type it in
    bool fileIsThere(string whatFolder, string whatFile);

    // going to save time, in order of miliseconds, orientaiton, date. The session argument is just for where its supposed to go
    void saveSolveNoOrientation(string session, long long milliseconds, string date);
    void saveSolveOrientation(string session, long long milliseconds, string orientation, string date);

    // getters 
    string getSessionName(); // returns current session file name
    string getSolveName(); // returns current algorithm file name
    string grabSolve(int index); // returns all solve information
    string getAlgorithm();

    // for the algorithmPractice class
    void writeAlgorithm();
    void drawAlgorithm(); 


    // for averaging
    long long grabAO5(); // returns miliseconds
    long long grabAO12();
    long long grabPB(); // returns lowest time
};