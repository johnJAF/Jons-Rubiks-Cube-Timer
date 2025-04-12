#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

// class to manage the data of any given function. Abstracted enough to be used universally
class DataManager {
public:
    bool fileIsThere();
    void createFile();
    void grabFileInfo(string fileThatYouWantInfoFrom);

    void displayFolder(string whatFolder);
    
    void writeAlgorithm();
    void drawAlgorithm(); 

    // going to save time, 
    void saveSolveNoOrientation(long long milliseconds, string date, string session);
    void saveSolveOrientation(long long milliseconds, string orientation, string date, string session);
};