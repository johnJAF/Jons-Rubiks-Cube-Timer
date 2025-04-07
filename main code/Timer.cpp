#include "Timer.h"

// original flags for turning the console settings back to normal.
int originalFlags = fcntl(STDIN_FILENO, F_GETFL);

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

// clears screen depending on system archetecture (UNIX/MAC ONLY RN)
void Timer::clearScreen() {
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
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

// used while timer is running - checks what time it is right now and then prints that
void Timer::printCurrent() {
    elapsedCurrent();

    TimeSpan meow(elapsedTimeForCurrent);

    meow.print();
}

void Timer::runTimer() {
    // this will block all of the terminals searches for terminal inputs and will stop the need to hit enter to stop the program
    setNonBlockingInput();

    cout << "Press any button to stop the timer\n";
    //sleep(5);
    char c = 0;

    start();

    // timer terminal printer 
    while (true) {
        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        // if any byte gets read from the terminal input then its gonna stop the program.
        if (bytesRead > 0) {
            break;
        }

        // if the program didnt need to break it will print running every 10 miliseconds.
        clearScreen();
        cout << "Press any button to stop the timer\n";
        printCurrent();
    }

    stop();
    clearScreen();
    
    cout << "Final Time: ";
    printTime();
    
    // this will restore all of the changes prevented when setNonBlockingInput was called
    restoreTerminal();
}

