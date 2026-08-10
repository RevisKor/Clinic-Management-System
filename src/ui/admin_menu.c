#include "../../include/ui/admin_menu.h"
#include "../../include/io.h"

void AdminMenu_Show(void) {
    printf("\n");
    printf("  ADMIN MENU\n");
    printf("  ------------------------\n");
    printf("  [1] View Patients\n");
    printf("  [2] View Appointments\n");
    printf("  [3] Delete Patient\n");
    printf("  [4] Delete Appointment\n");
    printf("  [5] Log Out\n");
    printf("  ------------------------\n");
    printf("\n");
    printf("  Selection > ");
}

void AdminMenu_Loop(PatientDatabase* patientDatabase, AppointmentDatabase* appointmentDatabase) {
    s32 choice;
    s32 isLoggedOut = 0;

    while (!isLoggedOut) {
        AdminMenu_Show();

        if (scanf("%ld", &choice) != 1) {
            Io_FlushStdin();
            continue;
        }
        Io_FlushStdin();

        switch (choice) {
            case 1:
                printf("Loading patient records...\n");
                sleep(OneSecondDelay);
                AdminMenu_PrintPatientDatabase(patientDatabase);
                break;

            case 2:
                printf("Loading appointment records...\n");
                sleep(OneSecondDelay);
                AdminMenu_PrintAppointmentDatabase(appointmentDatabase);
                break;

            case 3: {
                s32 patientId;

                // Show the list first so the admin knows which ID to pick.
                AdminMenu_PrintPatientDatabase(patientDatabase);

                if (patientDatabase->count == 0) {
                    sleep(OneSecondDelay);
                    break;
                }

                printf("\nEnter the patient ID to delete: ");
                if (scanf("%ld", &patientId) != 1) {
                    Io_FlushStdin();
                    printf("Invalid input.\n");
                    break;
                }
                Io_FlushStdin();

                printf("Deleting patient...\n");
                sleep(OneSecondDelay);

                if (Database_Delete(PatientDataFile, patientDatabase, PATIENT_TYPE, patientId)) {
                    printf("Patient deleted.\n");
                } else {
                    printf("Patient not found.\n");
                }

                sleep(OneSecondDelay);
                break;
            }

            case 4: {
                s32 selection;

                // Numbered so the admin can pick a row instead of retyping date/time by hand.
                AdminMenu_PrintAppointmentDatabase(appointmentDatabase);

                if (appointmentDatabase->count == 0) {
                    sleep(OneSecondDelay);
                    break;
                }

                printf("\nEnter the # of the appointment to delete: ");
                if (scanf("%ld", &selection) != 1) {
                    Io_FlushStdin();
                    printf("Invalid input.\n");
                    break;
                }
                Io_FlushStdin();

                printf("Deleting appointment...\n");
                sleep(OneSecondDelay);

                if (Appointment_CancelByIndex(appointmentDatabase, AppointmentDataFile, selection)) {
                    printf("Appointment deleted.\n");
                } else {
                    printf("Invalid selection.\n");
                }

                sleep(OneSecondDelay);
                break;
            }

            case 5:
                printf("Logging out ...\n");
                sleep(OneSecondDelay);
                isLoggedOut = 1;
                break;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}

void AdminMenu_PrintPatientDatabase(const PatientDatabase* database) {
    if (database == NULL || database->count == 0) {
        printf("\n=== Patient database is empty ===\n");
        return;
    }

    printf("\n=================================== PATIENT DATABASE ===================================\n");
    printf("%-10s | %-20s | %-12s | %-6s | %s\n", "ID", "Username", "Birth Date", "Gender", "Password Hash (first 10 chars)");
    printf("----------------------------------------------------------------------------------------\n");

    for (u32 index = 0; index < database->count; index++) {
        Patient patient = database->patients[index];

        // Truncated just for display so it doesn't blow up the terminal width.
        u8 shortHash[11];
        snprintf((char*) shortHash, sizeof(shortHash), "%.10s", (const char*) patient.passwordHash);

        printf("%-10ld | %-20s | %-12s | %-6c | %s...\n",
               patient.patientId,
               (const char*) patient.username,
               (const char*) patient.birthDate,
               patient.gender,
               (const char*) shortHash);
    }
    printf("========================================================================================\n");
    printf("Total patients: %lu / capacity: %lu\n", database->count, database->capacity);
}

void AdminMenu_PrintAppointmentDatabase(const AppointmentDatabase* database) {
    if (database == NULL || database->count == 0) {
        printf("\n=== Appointment database is empty ===\n");
        return;
    }

    printf("\n======================= APPOINTMENT DATABASE =======================\n");
    printf("%-4s | %-15s | %-15s | %-10s\n", "#", "Patient ID", "Date", "Time");
    printf("----------------------------------------------------------------------\n");

    for (u32 index = 0; index < database->count; index++) {
        Appointment appointment = database->appointments[index];
        printf("%-4lu | %-15ld | %-15s | %-10s\n",
               index + 1,
               appointment.patientId,
               (const char*) appointment.date,
               (const char*) appointment.time);
    }
    printf("========================================================================\n");
    printf("Total appointments: %lu / capacity: %lu\n", database->count, database->capacity);
}
