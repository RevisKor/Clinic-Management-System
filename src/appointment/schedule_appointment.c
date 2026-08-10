#include "../../include/appointment/schedule_appointment.h"
#include "../../include/io.h"

s32 Appointment_IsSlotTaken(AppointmentDatabase* database, const u8* date, const u8* time) {
    for (u32 index = 0; index < database->count; index++) {
        if (strcmp((const char*) database->appointments[index].date, (const char*) date) == 0 &&
            strcmp((const char*) database->appointments[index].time, (const char*) time) == 0) {
            return 1;
        }
    }

    return 0;
}

void Appointment_PrintAvailableTimes(AppointmentDatabase* database, const u8* date) {
    u32 openHour, openMinute, closeHour, closeMinute;

    sscanf((const char*) ClinicOpeningHours, "%lu:%lu", &openHour, &openMinute);
    sscanf((const char*) ClinicClosingHours, "%lu:%lu", &closeHour, &closeMinute);

    u32 openTotalMinutes = openHour * 60 + openMinute;
    u32 closeTotalMinutes = closeHour * 60 + closeMinute;

    s32 slotsFound = 0;

    printf("\n----- Available times on %s -----\n", (const char*) date);

    for (u32 minutes = openTotalMinutes; minutes <= closeTotalMinutes; minutes += SlotIntervalMinutes) {
        u8 slotTime[6];
        u32 displayHour = (minutes / 60) % 24;
        u32 displayMinute = minutes % 60;

        snprintf((char*) slotTime, sizeof(slotTime), "%02lu:%02lu", displayHour, displayMinute);

        if (!Appointment_IsSlotTaken(database, date, slotTime)) {
            printf("  %s\n", (const char*) slotTime);
            slotsFound++;
        }
    }

    if (slotsFound == 0) {
        printf("  No open slots left for this date.\n");
    }

    printf("----------------------------------\n");
}

void Appointment_Schedule(Patient* currentPatient, AppointmentDatabase* database) {
    u8 date[11] = {0};
    u8 time[6] = {0};

    s32 isValidSlot = 0;

    printf("\n===== Schedule Appointment =====\n");

    // Loop until the user enters a valid, open, free slot.
    while (!isValidSlot) {
        Date_GetDate((const u8*) "Enter the appointment date", date);

        if (Date_Validate(date)) {
            printf("Invalid date entered. Please try again.\n");
            sleep(OneSecondDelay);
            continue;
        }

        printf("Checking availability...\n");
        sleep(OneSecondDelay);

        Appointment_PrintAvailableTimes(database, date);

        Date_GetTime((const u8*) "Enter the appointment time", time);

        if (Date_ValidateOpeningHours(time, (u8*) ClinicOpeningHours, (u8*) ClinicClosingHours)) {
            printf("Clinic is only open between %s and %s. Please try again.\n", (const char*) ClinicOpeningHours, (const char*) ClinicClosingHours);
            sleep(OneSecondDelay);
            continue;
        }

        if (Appointment_IsSlotTaken(database, date, time)) {
            printf("This slot is already booked. Please choose another time.\n");
            sleep(OneSecondDelay);
            continue;
        }

        isValidSlot = 1;
    }

    printf("Booking your appointment...\n");
    sleep(OneSecondDelay);

    if (database->count >= database->capacity) {
        Database_Reallocate(database, APPOINTMENT_TYPE);
    }

    u32 index = database->count;

    database->appointments[index].patientId = currentPatient->patientId;
    strcpy((char*) database->appointments[index].date, (const char*) date);
    strcpy((char*) database->appointments[index].time, (const char*) time);

    database->count++;

    Database_Add(AppointmentDataFile, &database->appointments[index], APPOINTMENT_TYPE);

    printf("\n====================================\n");
    printf("| Appointment confirmed!\n");
    printf("| Date: %s\n", (const char*) date);
    printf("| Time: %s\n", (const char*) time);
    printf("====================================\n\n");

    Io_FlushStdin();

    printf("Press Enter to continue... ");
    getchar();
}
