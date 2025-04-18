#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <vector>
#include <filesystem>
#include <regex>

using namespace std;

// class to manage the data of any given function. Abstracted enough to be used universally
class DataManager {
    string sessionName;
    string algName;
    vector<string> fileInfoHolder;
    // if not editing mode we are in deleting mode
    bool editingMode; 

public:
    // file navigation
    bool createFile(string whatFolder, string fileName); // creates a session or an algorithm
    void createSessionLoop();
    bool isValidFilename(const string& name);
    bool deleteFile(string whatFolder, string whatFile); // deletes a file or session
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
    string getSolve(int index); // returns all solve information
    string getAlgCategory(string ollOrPll, int index);
    string displayAlgPhoto(string ollOrPll, string algorithm);


    // for the algorithmPractice class
    void writeAlgorithm();
    void drawAlgorithm(); 

    // for averaging
    long long grabAO5(); // returns miliseconds
    long long grabAO12();
    long long grabPB(); // returns lowest time
};