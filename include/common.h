#ifndef COMMON_H
#define COMMON_H

#ifdef _WIN32
    #ifndef WIN32_LEAN_AND_MEAN
    #define WIN32_LEAN_AND_MEAN
    #endif
    #include <windows.h>
    #include <conio.h>
#else
    #include <unistd.h>
    #include <sys/select.h>
    #include <termios.h>
    #include <fcntl.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <errno.h>

#define TIMER_DURATION 60
#define MIN_GMT_OFFSET -12
#define MAX_GMT_OFFSET 14
#define MAX_FORMAT 3

typedef struct {
    int gmt_offset;
    int dst_active;
    int time_format;
    int hour_format;
} TimeSettings;

/* Shared constants */
#define SECONDS_IN_A_MINUTE 60
#define SECONDS_IN_AN_HOUR 3600
#define DAYS_IN_A_YEAR 365
#define DAYS_IN_A_MONTH 30
#define DAYS_IN_A_WEEK 7

#endif
