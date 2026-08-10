#ifndef DATE_H
#define DATE_H

#include "../common.h"

s32 Date_IsLeapYear(s32 year);

// Prompts once and copies whatever the user typed (up to 10 chars) into
// destDate, without validating it - callers loop on Date_Validate themselves
// so they can show their own retry messaging.
void Date_GetDate(const u8* prompt, u8* destDate);

// Prompts until the user enters a syntactically valid HH:MM time (validated
// with Date_ValidateTime), then copies it into destTime.
void Date_GetTime(const u8* prompt, u8* destTime);

// Returns 0 if date is a real DD/MM/YYYY calendar date, 1 otherwise.
s32 Date_Validate(u8* date);

// Returns 0 if time is a syntactically valid HH:MM (00-23 / 00-59), 1 otherwise.
s32 Date_ValidateTime(u8* time);

// Returns 0 if time falls within [openingHours, closingHours] inclusive, 1 otherwise.
s32 Date_ValidateOpeningHours(u8* time, u8* openingHours, u8* closingHours);

#endif // DATE_H
