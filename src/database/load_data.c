#include "../../include/database/load_data.h"
#include "../../include/domain/patient.h"
#include "../../include/domain/appointment.h"

void Database_HandleAllocationFailure(void* databasePtr, DatabaseType type) {
    printf("Memory allocation failed ...\n");
    sleep(OneSecondDelay);
    printf("Terminating\n");

    if (databasePtr != NULL) {
        if (type == PATIENT_TYPE) {
            PatientDatabase* database = (PatientDatabase*) databasePtr;
            free(database->patients);

        } else if (type == APPOINTMENT_TYPE) {
            AppointmentDatabase* database = (AppointmentDatabase*) databasePtr;
            free(database->appointments);
        }
    }

    exit(MEMORY_ALLOCATION_ERROR);
}

void Database_Reallocate(void* databasePtr, DatabaseType type) {
    if (type == PATIENT_TYPE) {
        PatientDatabase* database = (PatientDatabase*) databasePtr;

        database->capacity *= 2;
        Patient* grown = realloc(database->patients, database->capacity * sizeof(Patient));

        if (grown == NULL) {
            Database_HandleAllocationFailure(database, PATIENT_TYPE);
        }

        database->patients = grown;
        return;

    } else if (type == APPOINTMENT_TYPE) {
        AppointmentDatabase* database = (AppointmentDatabase*) databasePtr;

        database->capacity *= 2;
        Appointment* grown = realloc(database->appointments, database->capacity * sizeof(Appointment));

        if (grown == NULL) {
            Database_HandleAllocationFailure(database, APPOINTMENT_TYPE);
        }

        database->appointments = grown;
        return;
    }

    printf("Internal error: unknown database type. Please check the code.\n");
    exit(INTERNAL_ERROR);
}

void Database_Load(const u8* file, void* databasePtr, DatabaseType type) {
    FILE* data = fopen((const char*) file, "r");

    if (!data) {
        printf("No existing data file found\n");
        sleep(OneSecondDelay);
        printf("Terminating ...\n");
        exit(FILE_NOT_FOUND_ERROR);
    }

    if (type == PATIENT_TYPE) {
        PatientDatabase* database = (PatientDatabase*) databasePtr;
        Patient patient;

        while (fscanf(data, "%64s %ld %64s %10s %c ",
            (char*) patient.username,
            &patient.patientId,
            (char*) patient.passwordHash,
            (char*) patient.birthDate,
            (char*) &patient.gender) == 5)
        {
            if (database->count >= database->capacity) {
                Database_Reallocate(database, PATIENT_TYPE);
            }

            database->patients[database->count] = patient;
            database->count++;
        }

    } else if (type == APPOINTMENT_TYPE) {
        AppointmentDatabase* database = (AppointmentDatabase*) databasePtr;
        Appointment appointment;

        while (fscanf(data, "%ld %10s %5s",
            &appointment.patientId,
            (char*) appointment.date,
            (char*) appointment.time) == 3)
        {
            if (database->count >= database->capacity) {
                Database_Reallocate(database, APPOINTMENT_TYPE);
            }

            database->appointments[database->count] = appointment;
            database->count++;
        }

    } else {
        printf("Internal error: unknown database type. Please check the code.\n");
        exit(INTERNAL_ERROR);
    }

    fclose(data);
}
