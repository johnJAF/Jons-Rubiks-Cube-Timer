#include "DataManager.h"
// file navigation 
// creates a session or an algorithm
void DataManager::createFile(string whatFolder, string fileName) {

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