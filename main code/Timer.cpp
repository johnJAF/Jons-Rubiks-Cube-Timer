#include "Timer.h"

// Set terminal to raw mode
void Timer::setNonBlockingInput() {
    termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    // Disable canonical mode and echo
    ttystate.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);

    // Set non-blocking mode
    int flags = fcntl(STDIN_FILENO, F_GETFL);
    flags |= O_NONBLOCK;
    fcntl(STDIN_FILENO, F_SETFL, flags);
}

// Restore terminal settings to normal
void Timer::restoreTerminal() {
    termios ttystate;
    tcgetattr(STDIN_FILENO, &ttystate);

    ttystate.c_lflag |= ICANON | ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &ttystate);
}