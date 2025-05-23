#include "DataManager.h"
namespace fs = std::filesystem;

// file navigation 
// creates a session or an algorithm
// whatFolder can be Algorithms or TimerSessions 
// returns true if created, false if typed in improperly. Implemented by programmer
// REMINDER: IMPLIMENT EXISTS LOGIC WHEN USED SO WHEN THE FILE EXISTS I KNOW TO JUST OPEN THAT FILE
bool DataManager::createFile(const string& whatFolder, const string& fileName) {
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

    // creates the file at the given path, if something was wrong with the file creation itll throw an error.
    ofstream meow(fullPath);
    if (!meow) {
        cerr << endl << "[Error] Failed to create file: " << fullPath << endl;
        return false;
    }

    if (whatFolder == "OLL" || whatFolder == "PLL") {
        algName = fileName;
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
        sessionName = file;
    }
}

// deletes a file or session
bool DataManager::deleteFile(const string& whatFolder, const string& whatFile) {
    fs::path basePath = fs::absolute("Data/" + whatFolder);
    fs::path extension = ".txt";
    fs::path fullPath = basePath / whatFile += extension;

    if (!isValidFilename(whatFile)) {
        cerr << endl << "[Error] Invalid file name. Use only letters, numbers, -, _." << endl;
        return false; // program escape to say name wasnt good
    }

    if (fs::exists(fullPath)) { // if the file path exists
        if (fs::remove(fullPath)) { // delete that exact file
            cout << "Deleted: " << fullPath << endl;
            return true;
        } else {
            cerr << "Failed to delete: " << fullPath << endl;
            return false;
        }
    } else { // only if file doesnt exist
        cerr << "File does not exist: " << fullPath << endl;
        return false;
    }

}

// prints the feature folder
// folder can only be algorithms -> OLL, PLL -> (alg names depending on o/pll)
// or the folder can be sessions -> (all session names)
void DataManager::displayFolder(const string& whatFolder) {
    fs::path basePath = fs::absolute("Data/" + whatFolder);

    for (auto const& dir_entry : fs::directory_iterator{basePath}) {
        if (dir_entry.path().filename() == ".gitkeep") {
            continue; // skip it
        }

        cout << dir_entry.path().filename() << endl;
    }
}

// grabs all file info as a dynamic vector and stores it to fileInfoHolder
// make whatFolder "" in order to grab the oll/pll algs/algphoto txt files
void DataManager::vectorFileInfo(const string& whatFolder, const string& whatFile) {
    fs::path basePath = fs::absolute("Data/" + whatFolder);
    fs::path extension = ".txt";
    fs::path fullPath = basePath / whatFile += extension;
    string line;

    // just making sure everything works 
    if (!isValidFilename(whatFile)) {
        cerr << endl << "[Error] Invalid file name. Use only letters, numbers, -, _." << endl;
        return; // program escape to say name wasnt good
    }

    ifstream meow(fullPath);

    while(getline(meow, line)) {
        fileInfoHolder.emplace_back(line);
    }

    fileInfoHolder.pop_back(); // removes white space

    meow.close();
}

// i created this method because it does vectorFileInfo but it has more power because it doesnt check if the file name is valid, it just runs it
// only use it if you know the exact path
void DataManager::vectorFileInfo(const fs::path& fully) {
    string line;

    if (!fs::exists(fully)) {
        return;
    }

    ifstream meow(fully);

    if (!meow.is_open()) {
        return;
    }

    while (getline(meow, line)) {
        fileInfoHolder.emplace_back(line);
    }

    meow.close();
}

// going to save time, in order of miliseconds, orientaiton, date. The session argument is just for where its supposed to go
void DataManager::saveSolveNoOrientation(const string& session, const long long milliseconds, const string& date) {
    fs::path basePath = fs::absolute("Data/Sessions");
    fs::path extension = ".txt";
    fs::path fullPath = basePath / session += extension;

    if (fs::exists(fullPath)) {
        cout << endl << "[Notice] File already exists. Choose another name." << endl;
        return;
    }
}

void DataManager::saveSolveOrientation(const string& session, const long long milliseconds, const string& orientation, const string& date) {

}

bool DataManager::saveAlgTime(const string& ollpll, const string& specificAlgName, const long long milliseconds, const char date[50]) {
    fs::path fullPath;

    if (ollpll == "oll") {
        fs::path basePath = fs::absolute("Data/Algorithms/OLL");
        fs::path extension = ".txt";
        fullPath = basePath / specificAlgName += extension;
    } else if (ollpll == "pll") {
        fs::path basePath = fs::absolute("Data/Algorithms/PLL");
        fs::path extension = ".txt";
        fullPath = basePath / specificAlgName += extension;
    }

    ofstream meow(fullPath, ios_base::app);
    
    if (!meow) { // if the file isnt created for some reason then we will error out
        cerr << endl << "[Error] Failed to create file: " << fullPath << endl;
        return false;
    }
    
    meow << specificAlgName << ":" << milliseconds << ":" << date << endl;;

    meow.close();

    return true;
}

long long DataManager::getLatestAlgTime(const string& ollpll, const string& whatAlgorithm) {
    fs::path fullPath;
    string algName;
    string algTime;
    string algDate;
    string holder;

    vector<string> allTimes;

    long long time;

    if (ollpll == "oll") {
        fs::path basePath = fs::absolute("Data/Algorithms/OLL");
        fs::path extension = ".txt";
        fullPath = basePath / whatAlgorithm += extension;
    } else if (ollpll == "pll") {
        fs::path basePath = fs::absolute("Data/Algorithms/PLL");
        fs::path extension = ".txt";
        fullPath = basePath / whatAlgorithm += extension;
    }

    if (!fileInfoHolder.empty()) {
        fileInfoHolder.clear();
    }

    vectorFileInfo(fullPath);

    if (fileInfoHolder.empty()) {
        return 0;
    }

    holder = fileInfoHolder.back();

    stringstream ss(holder);

    getline(ss, algName, ':');
    getline(ss, algTime, ':'); // should hold the alg timer
    getline(ss, algDate);

    time = stoll(algTime);

    return time;
}

void DataManager::undoTime(const string& ollpll, const string& whatAlgorithm) {
    fs::path fullPath;
    string algName;
    string algTime;
    string algDate;
    string holder;

    vector<string> allTimes;

    long long time;

    if (ollpll == "oll") {
        fs::path basePath = fs::absolute("Data/Algorithms/OLL");
        fs::path extension = ".txt";
        fullPath = basePath / whatAlgorithm += extension;
    } else if (ollpll == "pll") {
        fs::path basePath = fs::absolute("Data/Algorithms/PLL");
        fs::path extension = ".txt";
        fullPath = basePath / whatAlgorithm += extension;
    }

    if (!fileInfoHolder.empty()) {
        fileInfoHolder.clear();
    }

    vectorFileInfo(fullPath);

    // If file is not empty
    if (!fileInfoHolder.empty()) {
        fileInfoHolder.pop_back();  // Remove the last line
    }

    // Write lines back to the same file (overwrite)
    ofstream of(fullPath, ios::trunc);  // trunc clears the file
    for (const string& s : fileInfoHolder) {
        of << s << '\n';
    }
    of.close();
}


// // getters 
// // returns current session file name
// string DataManager::getSessionName() {

// }

// // returns current algorithm file name
// string DataManager::getSolveName() {

// }

// // returns all solve information
// string DataManager::getSolve(int index) {

// }

// string DataManager::getAlgCategory(string ollOrPll, int index) {

// }

// string DataManager::displayAlgPhoto(string ollOrPll, string algorithm) {

// }


// // for the algorithmPractice class
// void DataManager::writeAlgorithm() {

// }

// void DataManager::drawAlgorithm() {

// }


// for averaging
// returns miliseconds
long long DataManager::grabAO5() {

}

long long DataManager::grabAO12() {

}

// returns lowest time
long long DataManager::grabPB(const string& ollpll, const string& whatAlgorithm) {
    fs::path fullPath;
    string algName;
    string algTime;
    string algDate;

    long long time;

    if (ollpll == "oll") {
        fs::path basePath = fs::absolute("Data/Algorithms/OLL");
        fs::path extension = ".txt";
        fullPath = basePath / whatAlgorithm += extension;
    } else if (ollpll == "pll") {
        fs::path basePath = fs::absolute("Data/Algorithms/PLL");
        fs::path extension = ".txt";
        fullPath = basePath / whatAlgorithm += extension;
    }

    if (!fileInfoHolder.empty()) {
        fileInfoHolder.clear();
    }

    vectorFileInfo(fullPath);

    if (fileInfoHolder.empty()) {
        return 0;
    }

    long long personalBest = numeric_limits<long long>::max();

    // logic to grab the quickest time
    // Aa Perm:7043:05/08/25
    for (string s : fileInfoHolder) {
        stringstream ss(s);

        getline(ss, algName, ':'); // "Aa Perm"
        getline(ss, algTime, ':'); // "7042"
        getline(ss, algDate); // "05/08/25"

        time = stoll(algTime); // 7042

        if (time < personalBest) {
            personalBest = time;
        }
    }

    return personalBest;
}