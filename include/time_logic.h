#ifndef TIME_LOGIC_H
#define TIME_LOGIC_H

#include "common.h"

extern TimeSettings settings;

void displayTime(int seconds);
void runTimer(void);
void runStopwatch(void);
void runClock(void);
void decipherUnixTimestamp(void);
void convertSeconds(void);
void setGMTOffset(void);
void toggleDST(void);
void toggleTimeFormat(void);
void toggleHourFormat(void);
void formatTime(char *buffer, size_t bufferSize, const struct tm *time_info);

#ifdef _WIN32
double getElapsedTime(LARGE_INTEGER *start, LARGE_INTEGER *end);
#endif

#endif
