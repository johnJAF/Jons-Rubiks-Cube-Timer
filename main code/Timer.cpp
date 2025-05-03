#include "Timer.h"

// original flags for turning the console settings back to normal.

// starts the timer
void Timer::start() {
    startTime = Clock::now();
}

// returns elapsed time
void Timer::stop() {
    stopTime = Clock::now();
    elapsedTime = duration_cast<milliseconds>(stopTime - startTime).count();
}

// Set terminal to ignore rules mode
void Timer::setNonBlockingInput() {
    // terminos is a struct that holds terminal settings
    termios ttystate;
    // terminal current get attribute (gets all terminal settings, and input then throws them into ttystate)
    tcgetattr(STDIN_FILENO, &ttystate);

    // c_lflag controls terminal input behavior ~ ICANON removes hitting enter from terminal ECHO doesnt show the typed character in terminal
    ttystate.c_lflag &= ~(ICANON | ECHO);
    // applies the changes to ttystate right now (TCSANOW)
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    // fcntl sets file descriptor flags, F_GETFL sets them to the current ones
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    // making the flags O_NONBLOCK keeps the terminal from pausing on a newline and just absorbs the input
    flags |= O_NONBLOCK;
    // sets current flags to flags
    fcntl(STDIN_FILENO, F_SETFL, flags);
}

// Restore terminal settings to normal
void Timer::restoreTerminal() {
    // get current settings
    termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    // restores original flags
    ttystate.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    // restore original file flags
    fcntl(STDIN_FILENO, F_SETFL, originalFlags);
}

// get the width of the terminal in order to print centered text
int Timer::getTerminalWidth() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
    return w.ws_col;
}

// prints centered text in terminal
void Timer::printCentered(const string& text) {
    int width = getTerminalWidth();
    int padding = (width - text.length()) / 2;
    if (padding > 0)
        cout << setfill(' ') << setw(padding) << " " << text << endl;
    else
        cout << text << endl; // fallback if terminal too narrow
}

string Timer::centered(const string& text) {
    int width = 80; // adjust as needed
    int padding = max((width - static_cast<int>(text.length())) / 2, 0);
    return string(padding, ' ') + text;
}

// prints two columns taking in two string references
void Timer::printTwoColumns(const string& left, const string& right) {
    int width = getTerminalWidth();
    int half = width / 2;

    // Calculate padding for left and right columns
    int leftPadding = (half - left.length()) / 2;
    int rightPadding = half + (half - right.length()) / 2;

    // Print left string
    cout << setfill(' ') << setw(leftPadding) << " " << left;

    // Move to right column position
    cout << setfill(' ') << setw(rightPadding - leftPadding - left.length()) << " " << right << endl;
}

// clears screen depending on system archetecture (UNIX/MAC ONLY RN)
void Timer::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

void Timer::flushInputBuffer() {
    char junk;
    while (read(STDIN_FILENO, &junk, 1) > 0) {
        // discard all buffered input
    }
}

// while timer is running - used to grab the time now - start time.
void Timer::elapsedCurrent() {
    elapsedTimeForCurrent = duration_cast<milliseconds>(Clock::now() - startTime).count();
}

// prints final elapsed time
void Timer::printTime() {
    TimeSpan meow(elapsedTime);

    meow.print();
}

long long Timer::returnFinalTime() {
    return elapsedTime;
}

// used while timer is running - checks what time it is right now and then prints that
void Timer::printCurrent() {
    elapsedCurrent();
    string moo = "";

    TimeSpan meow(elapsedTimeForCurrent);

    moo = meow.grabTime();

    printCentered(moo);
}

void Timer::runTimer() {
    // this will block all of the terminals searches for terminal inputs and will stop the need to hit enter to stop the program
    setNonBlockingInput();

    char c = 0;

    start();

    // timer terminal printer 
    while (true) {
        c = 0;

        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        // if any byte gets read from the terminal input then its gonna stop the program.
        if (bytesRead > 0) {
            break;
        }

        // if the program didnt need to break will constantly print the running timer.
        clearScreen();
        cout << endl << endl << endl;
        printCentered("Press any button to stop the timer");
        cout << endl;
        printCurrent();
    }

    stop();
    clearScreen();
    
    // this will restore all of the changes prevented when setNonBlockingInput was called
    restoreTerminal();
}

void Timer::runTimer(string algorithm) {
// this will block all of the terminals searches for terminal inputs and will stop the need to hit enter to stop the program
    setNonBlockingInput();

    char c = 0;

    start();

    // timer terminal printer 
    while (true) {
        c = 0;

        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        // if any byte gets read from the terminal input then its gonna stop the program.
        if (bytesRead > 0) {
            break;
        }

        // if the program didnt need to break will constantly print the running timer.
        clearScreen();
        cout << endl << endl << endl;
        printCentered("Press any button to stop the timer");
        cout << endl;
        printCurrent();
        cout << endl << endl << endl;
        printCentered(algorithm);
    }

    stop();
    clearScreen();
    
    // this will restore all of the changes prevented when setNonBlockingInput was called
    restoreTerminal();
}

// 15 second timer countdown
void Timer::inspectionTime() {
    Clock::time_point inspectionStart;
    Clock::time_point inspectionStop;
    long long timeRightNow;
    long long inspectionLimit;

    if(!inspectionOn) {
        return;
    }

    setNonBlockingInput();

    cout << "Press any button to stop the timer\n";

    char c = 0;
    string mooski = "";

    inspectionStart = Clock::now();

    // timer terminal printer 
    while (true) {
        c = 0;

        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        // if any byte gets read from the terminal input then its gonna stop the program.
        if (bytesRead > 0) {
            break;
        }

        // if the program didnt need to break it will print the current time
        clearScreen();

        cout << endl << endl << endl;
        printCentered("Press any button to stop the timer");
        cout << endl;

        long long timeRightNow = duration_cast<milliseconds>((Clock::now() - inspectionStart)).count();
        
        long long inspectionLimit = 15000;

        if (timeRightNow >= inspectionLimit) {
            break;
        } else {
            inspectionLimitReached = false;
        }

        TimeSpan meow(15000-duration_cast<milliseconds>((Clock::now() - inspectionStart)).count());

        mooski = meow.grabTime();

        printCentered(mooski);

    }

    clearScreen();

    if (timeRightNow >= inspectionLimit) {
            cout << endl << "Coutdown is over";
            inspectionLimitReached = true;
        }
    
    
    
    // this will restore all of the changes prevented when setNonBlockingInput was called
    restoreTerminal();
}

void Timer::timerScreen() {

}