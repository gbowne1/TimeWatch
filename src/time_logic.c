#include "time_logic.h"
#include "ui.h"

TimeSettings settings = {0, 0, 0, 24};

#ifdef _WIN32
double getElapsedTime(LARGE_INTEGER *start, LARGE_INTEGER *end) {
    LARGE_INTEGER freq;
    QueryPerformanceFrequency(&freq);
    return (double)(end->QuadPart - start->QuadPart) / (double)freq.QuadPart;
}
#endif

void displayTime(int seconds) {
    int hours = seconds / SECONDS_IN_AN_HOUR;
    int remainder = seconds % SECONDS_IN_AN_HOUR;
    int minutes = remainder / SECONDS_IN_A_MINUTE;
    int remaining_seconds = remainder % SECONDS_IN_A_MINUTE;
    printf("%02d:%02d:%02d", hours, minutes, remaining_seconds);
}

void formatTime(char *buffer, size_t bufferSize, const struct tm *time_info) {
    static const char *formats[] = {"%Y-%m-%d ", "%d/%m/%Y ", "%m/%d/%Y ", "%a, %d %b %Y "};
    static const char *hour_formats[] = {"%H:%M:%S", "%I:%M:%S"};

    strftime(buffer, bufferSize, formats[settings.time_format], time_info);
    strftime(buffer + strlen(buffer), bufferSize - strlen(buffer), 
             hour_formats[settings.hour_format == 12 ? 1 : 0], time_info);

    if (settings.hour_format == 12) {
        snprintf(buffer + strlen(buffer), bufferSize - strlen(buffer), 
                 time_info->tm_hour >= 12 ? " PM" : " AM");
    }
}

/* ... (Remaining functions runTimer, runStopwatch, runClock, etc. follow the same logic as your original snippet) ... */

void convertSeconds(void) {
    long total_seconds;
    printf("Enter the number of seconds: ");
    if (scanf("%ld", &total_seconds) != 1) {
        fprintf(stderr, "Invalid input.\n");
        while (getchar() != '\n');
        return;
    }

    int years = total_seconds / (DAYS_IN_A_YEAR * SECONDS_IN_AN_HOUR * 24);
    total_seconds %= (DAYS_IN_A_YEAR * SECONDS_IN_AN_HOUR * 24);
    int days = total_seconds / (SECONDS_IN_AN_HOUR * 24);
    total_seconds %= (SECONDS_IN_AN_HOUR * 24);
    int hours = total_seconds / SECONDS_IN_AN_HOUR;
    total_seconds %= SECONDS_IN_AN_HOUR;
    int minutes = total_seconds / SECONDS_IN_A_MINUTE;
    int seconds = total_seconds % SECONDS_IN_A_MINUTE;

    printf("Result: %d years, %d days, %d hours, %d minutes, %d seconds\n",
           years, days, hours, minutes, seconds);
}

void toggleDST(void) {
    settings.dst_active = !settings.dst_active;
    printf("DST is now %s\n", settings.dst_active ? "ON" : "OFF");
}

void setGMTOffset(void) {
    int new_offset;
    printf("Enter GMT offset (-12 to +14): ");
    if (scanf("%d", &new_offset) == 1 && new_offset >= MIN_GMT_OFFSET && new_offset <= MAX_GMT_OFFSET) {
        settings.gmt_offset = new_offset;
    } else {
        printf("Invalid offset.\n");
        while (getchar() != '\n');
    }
}

void toggleTimeFormat(void) {
    settings.time_format = (settings.time_format + 1) % (MAX_FORMAT + 1);
}

void toggleHourFormat(void) {
    settings.hour_format = (settings.hour_format == 12) ? 24 : 12;
}

void runClock(void) {
    time_t rawtime;
    struct tm *local_time, gmt_time;
    char local_buffer[80], gmt_buffer[80];
    int running = 1;

    disableBuffering();
    while (running) {
        time(&rawtime);
        local_time = localtime(&rawtime);
        gmt_time = *gmtime(&rawtime);

        gmt_time.tm_hour += settings.gmt_offset + (settings.dst_active ? 1 : 0);
        mktime(&gmt_time);

        formatTime(local_buffer, sizeof(local_buffer), local_time);
        formatTime(gmt_buffer, sizeof(gmt_buffer), &gmt_time);

        clearScreen();
        printf("Local Time: %s\n", local_buffer);
        printf("User GMT Time (GMT%+d): %s\n", settings.gmt_offset, gmt_buffer);
        printf("\n[q] Quit | [o] Offset | [d] DST | [f] Format | [h] 12/24\n");

        #ifdef _WIN32
        Sleep(200);
        #else
        usleep(200000);
        #endif

        if (kbhit()) {
            char ch = getchar();
            if (ch == 'q') running = 0;
            else if (ch == 'o') setGMTOffset();
            else if (ch == 'd') toggleDST();
            else if (ch == 'f') toggleTimeFormat();
            else if (ch == 'h') toggleHourFormat();
        }
    }
    enableBuffering();
}

void runTimer(void) {
    int remaining = TIMER_DURATION;
    time_t start = time(NULL);
    disableBuffering();
    while (remaining > 0 && !kbhit()) {
        clearScreen();
        printf("Remaining: "); displayTime(remaining);
        printf("\nPress any key to stop.\n");
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
        remaining = TIMER_DURATION - (int)difftime(time(NULL), start);
    }
    enableBuffering();
    printf("\nTimer Finished!\n");
    getchar();
}

void runStopwatch(void) {
    int elapsed = 0;
    time_t start = time(NULL);
    disableBuffering();
    while (!kbhit()) {
        clearScreen();
        printf("Elapsed: "); displayTime(elapsed);
        printf("\nPress any key to stop.\n");
        #ifdef _WIN32
        Sleep(1000);
        #else
        sleep(1);
        #endif
        elapsed = (int)difftime(time(NULL), start);
    }
    enableBuffering();
    printf("\nFinal Time: "); displayTime(elapsed);
    printf("\n");
    getchar();
}

void decipherUnixTimestamp(void) {
    time_t ts;
    printf("Enter Unix timestamp: ");
    if (scanf("%lld", (long long *)&ts) == 1) {
        printf("UTC: %s", asctime(gmtime(&ts)));
    }
}
