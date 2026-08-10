#include "../../include/ui/user_menu.h"
#include "../../include/io.h"

void UserMenu_Show(void) {
    printf("\n");
    printf("  PATIENT MENU\n");
    printf("  ------------------------\n");
    printf("  [1] Schedule Appointment\n");
    printf("  [2] Cancel Appointment\n");
    printf("  [3] Log Out\n");
    printf("  ------------------------\n");
    printf("\n");
    printf("  Selection > ");
}

void UserMenu_Loop(Patient* currentPatient, AppointmentDatabase* appointmentDatabase) {
    s32 choice;
    s32 isLoggedOut = 0;

    while (!isLoggedOut) {
        UserMenu_Show();

        if (scanf("%ld", &choice) != 1) {
            Io_FlushStdin();
            continue;
        }
        Io_FlushStdin();

        switch (choice) {
            case 1:
                Appointment_Schedule(currentPatient, appointmentDatabase);
                break;

            case 2: {
                s32 appointmentCount = Appointment_PrintUserAppointments(appointmentDatabase, currentPatient->patientId);

                if (appointmentCount == 0) {
                    sleep(OneSecondDelay);
                    break;
                }

                s32 selection;

                printf("\nEnter the number of the appointment to cancel: ");
                if (scanf("%ld", &selection) != 1) {
                    Io_FlushStdin();
                    printf("Invalid input.\n");
                    break;
                }
                Io_FlushStdin();

                if (selection < 1 || selection > appointmentCount) {
                    printf("Invalid selection.\n");
                    sleep(OneSecondDelay);
                    break;
                }

                printf("Cancelling appointment...\n");
                sleep(OneSecondDelay);

                if (Appointment_CancelByNumber(appointmentDatabase, AppointmentDataFile, currentPatient->patientId, selection)) {
                    printf("Appointment cancelled.\n");
                } else {
                    printf("Something went wrong, appointment not found.\n");
                }

                sleep(OneSecondDelay);
                break;
            }

            case 3:
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
