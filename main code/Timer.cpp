#include "Timer.h"

int originalFlags = fcntl(STDIN_FILENO, F_GETFL);




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