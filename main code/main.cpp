#include "Timer.h"


int main() {
    
    Timer meow;

    // this will block all of the terminals searches for terminal inputs and will stop the need to hit enter to stop the program
    meow.setNonBlockingInput();

    cout << "Press any button to stop the timer\n";
    sleep(5);
    char c = 0;

    while (true) {
        // reads one byte from the "standard input" which is the keyboard, &c is where the input character is stored, bytes read should be 1
        ssize_t bytesRead = read(STDIN_FILENO, &c, 1);
        // if any byte gets read from the terminal input then its gonna stop the program.
        if (bytesRead > 0) {
            cout << "FINAL TIME!\n";
            break;
        }

        // if the program didnt need to break it will print running every 10 miliseconds.
        cout << "mm:ss:ms\n";
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }

    // this will restore all of the changes prevented when setNonBlockingInput was called
    meow.restoreTerminal();
    return 0;
}