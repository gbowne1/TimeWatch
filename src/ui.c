#include "ui.h"
#include "common.h"

void clearScreen(void) {
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

int kbhit(void) {
    #ifdef _WIN32
    return _kbhit();
    #else
    struct timeval tv = {0L, 0L};
    fd_set fds;
    FD_ZERO(&fds);
    FD_SET(STDIN_FILENO, &fds);
    struct termios oldt, newt;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    int result = select(STDIN_FILENO + 1, &fds, NULL, NULL, &tv);
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return result > 0;
    #endif
}

void disableBuffering(void) {
    #ifndef _WIN32
    struct termios term;
    tcgetattr(0, &term);
    term.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(0, TCSANOW, &term);
    #endif
}

void enableBuffering(void) {
    #ifndef _WIN32
    struct termios term;
    tcgetattr(STDIN_FILENO, &term);
    term.c_lflag |= (ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &term);
    #endif
}
