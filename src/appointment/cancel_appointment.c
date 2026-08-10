#include "../../include/appointment/cancel_appointment.h"
#include "../../include/io.h"

s32 Appointment_PrintUserAppointments(const AppointmentDatabase* database, s32 patientId) {
    s32 count = 0;

    printf("\n===== Your Appointments =====\n");

    for (u32 index = 0; index < database->count; index++) {
        if (database->appointments[index].patientId == patientId) {
            count++;
            printf("  [%ld] %s at %s\n", count, (const char*) database->appointments[index].date, (const char*) database->appointments[index].time);
        }
    }

    if (count == 0) {
        printf("  You have no appointments booked.\n");
    }

    printf("==============================\n");

    return count;
}

s32 Appointment_Cancel(AppointmentDatabase* database, const u8* file, s32 patientId, const u8* date, const u8* time) {
    for (u32 index = 0; index < database->count; index++) {
        if (database->appointments[index].patientId == patientId &&
            strcmp((const char*) database->appointments[index].date, (const char*) date) == 0 &&
            strcmp((const char*) database->appointments[index].time, (const char*) time) == 0) {

            // Shift every entry after the cancelled one back by one position.
            for (u32 shiftIndex = index; shiftIndex < database->count - 1; shiftIndex++) {
                database->appointments[shiftIndex] = database->appointments[shiftIndex + 1];
            }

            database->count--;

            Database_Update(file, database, APPOINTMENT_TYPE);
            return 1;
        }
    }

    return 0;
}

s32 Appointment_CancelByNumber(AppointmentDatabase* database, const u8* file, s32 patientId, s32 selection) {
    s32 currentNumber = 0;

    for (u32 index = 0; index < database->count; index++) {
        if (database->appointments[index].patientId == patientId) {
            currentNumber++;

            if (currentNumber == selection) {
                u8 date[11];
                u8 time[6];

                strcpy((char*) date, (const char*) database->appointments[index].date);
                strcpy((char*) time, (const char*) database->appointments[index].time);

                return Appointment_Cancel(database, file, patientId, date, time);
            }
        }
    }

    return 0;
}

s32 Appointment_CancelByIndex(AppointmentDatabase* database, const u8* file, s32 index) {
    // Check the lower bound while still signed, before comparing against the
    // unsigned count.
    if (index < 1) {
        return 0;
    }

    u32 arrayIndex = (u32) (index - 1);

    if (arrayIndex >= database->count) {
        return 0;
    }

    // Shift every entry after the cancelled one back by one position.
    for (u32 shiftIndex = arrayIndex; shiftIndex < database->count - 1; shiftIndex++) {
        database->appointments[shiftIndex] = database->appointments[shiftIndex + 1];
    }

    database->count--;

    Database_Update(file, database, APPOINTMENT_TYPE);
    return 1;
}
