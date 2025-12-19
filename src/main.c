#include "common.h"
#include "ui.h"
#include "time_logic.h"

int main(void) {
    int choice;

    while (1) {
        printf("\n--- Timewatch Utility ---\n");
        printf("1. Timer\n2. Stopwatch\n3. Clock\n4. Decipher Unix Timestamp\n5. Convert Seconds\n6. Exit\n");
        printf("Choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1: runTimer(); break;
            case 2: runStopwatch(); break;
            case 3: runClock(); break;
            case 4: decipherUnixTimestamp(); break;
            case 5: convertSeconds(); break;
            case 6: return 0;
            default: printf("Invalid option.\n");
        }
    }
}
