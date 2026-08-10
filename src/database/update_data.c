#include "../../include/database/update_data.h"
#include "../../include/domain/patient.h"
#include "../../include/domain/appointment.h"

void Database_Add(const u8* file, void* entry, DatabaseType type) {
    FILE* data = fopen((const char*) file, "a");

    if (data == NULL) {
        printf("Loading file failed ...\n");
        sleep(OneSecondDelay);
        printf("Terminating\n");
        exit(MEMORY_ALLOCATION_ERROR);
    }

    if (type == PATIENT_TYPE) {
        Patient* patient = (Patient*) entry;

        if (fprintf(data, "%s %ld %64s %s %c \n",
            (const char*) patient->username,
            patient->patientId,
            (const char*) patient->passwordHash,
            (const char*) patient->birthDate,
            patient->gender) < 0)
        {
            printf("Failed to write account to database\n");
            fclose(data);
            exit(MEMORY_ALLOCATION_ERROR);
        }

        fclose(data);

    } else if (type == APPOINTMENT_TYPE) {
        Appointment* appointment = (Appointment*) entry;

        if (fprintf(data, "%ld %10s %5s\n",
            appointment->patientId,
            (const char*) appointment->date,
            (const char*) appointment->time) < 0)
        {
            printf("Failed to write appointment to database\n");
            fclose(data);
            exit(MEMORY_ALLOCATION_ERROR);
        }

        fclose(data);
    }
}

void Database_Update(const u8* file, void* databasePtr, DatabaseType type) {
    FILE* data = fopen((const char*) file, "w");

    if (type == PATIENT_TYPE) {
        PatientDatabase* database = (PatientDatabase*) databasePtr;

        for (u32 index = 0; index < database->count; index++) {
            fprintf(data, "%s %ld %64s %s %c \n",
                (const char*) database->patients[index].username,
                database->patients[index].patientId,
                (const char*) database->patients[index].passwordHash,
                (const char*) database->patients[index].birthDate,
                database->patients[index].gender);
        }

        fclose(data);

    } else if (type == APPOINTMENT_TYPE) {
        AppointmentDatabase* database = (AppointmentDatabase*) databasePtr;

        for (u32 index = 0; index < database->count; index++) {
            fprintf(data, "%ld %s %5s\n",
                database->appointments[index].patientId,
                (const char*) database->appointments[index].date,
                (const char*) database->appointments[index].time);
        }

        fclose(data);
    }
}

s32 Database_Delete(const u8* file, void* databasePtr, DatabaseType type, s32 id) {
    if (type == PATIENT_TYPE) {
        PatientDatabase* database = (PatientDatabase*) databasePtr;

        for (u32 index = 0; index < database->count; index++) {
            if (database->patients[index].patientId == id) {

                // Shift every entry after the deleted one back by one position.
                for (u32 shiftIndex = index; shiftIndex < database->count - 1; shiftIndex++) {
                    database->patients[shiftIndex] = database->patients[shiftIndex + 1];
                }

                database->count--;
                Database_Update(file, database, PATIENT_TYPE);
                return 1;
            }
        }

        printf("Patient ID not found in database\n");
        return 0;

    } else if (type == APPOINTMENT_TYPE) {
        AppointmentDatabase* database = (AppointmentDatabase*) databasePtr;

        for (u32 index = 0; index < database->count; index++) {
            if (database->appointments[index].patientId == id) {

                // Shift every entry after the deleted one back by one position.
                for (u32 shiftIndex = index; shiftIndex < database->count - 1; shiftIndex++) {
                    database->appointments[shiftIndex] = database->appointments[shiftIndex + 1];
                }

                database->count--;
                Database_Update(file, database, APPOINTMENT_TYPE);
                return 1;
            }
        }

        printf("Appointment not found in database\n");
        return 0;
    }

    printf("Internal error: unknown database type. Please check the code.\n");
    exit(INTERNAL_ERROR);
}
