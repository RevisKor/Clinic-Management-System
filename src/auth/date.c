#include "../../include/auth/date.h"
#include "../../include/io.h"

s32 Date_IsLeapYear(s32 year) {
    return (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
}

void Date_GetDate(const u8* prompt, u8* destDate) {
    printf("%s (DD/MM/YYYY): ", (const char*) prompt);
    fflush(stdout);

    if (fgets((char*) destDate, 11, stdin) != NULL) {
        destDate[strcspn((const char*) destDate, "\n")] = '\0';
    }
}

void Date_GetTime(const u8* prompt, u8* destTime) {
    u8 inputBuffer[6];

    do {
        printf("%s (HH:MM): ", (const char*) prompt);
        scanf("%5s", (char*) inputBuffer);
        Io_FlushStdin();

    } while (Date_ValidateTime(inputBuffer));

    strcpy((char*) destTime, (const char*) inputBuffer);
}

s32 Date_Validate(u8* date) {
    u32 day, month, year;
    u32 daysInMonth[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    sscanf((const char*) date, "%lu/%lu/%lu", &day, &month, &year);

    if (year < 1900 || year > 2100) {
        return 1;
    }

    if (month < 1 || month > 12) {
        return 1;
    }

    if (month == 2 && Date_IsLeapYear(year)) {
        daysInMonth[1] = 29;
    }

    return !(day <= daysInMonth[month - 1]);
}

s32 Date_ValidateTime(u8* time) {
    u32 hours, minutes;

    sscanf((const char*) time, "%lu:%lu", &hours, &minutes);

    if (hours > 23) {
        return 1;
    }

    if (minutes > 59) {
        return 1;
    }

    return 0;
}

s32 Date_ValidateOpeningHours(u8* time, u8* openingHours, u8* closingHours) {
    u32 timeParts[2], openParts[2], closeParts[2];

    // Break each "HH:MM" string into hours [0] and minutes [1].
    sscanf((const char*) time,          "%lu:%lu", &timeParts[0],  &timeParts[1]);
    sscanf((const char*) openingHours,  "%lu:%lu", &openParts[0],  &openParts[1]);
    sscanf((const char*) closingHours,  "%lu:%lu", &closeParts[0], &closeParts[1]);

    u32 timeMinutes  = timeParts[0]  * 60 + timeParts[1];
    u32 openMinutes  = openParts[0]  * 60 + openParts[1];
    u32 closeMinutes = closeParts[0] * 60 + closeParts[1];

    if (timeMinutes < openMinutes || timeMinutes > closeMinutes) {
        return 1;
    }

    return 0;
}
