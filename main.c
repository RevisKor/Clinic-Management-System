#include "include/common.h"
#include "include/domain/patient.h"
#include "include/domain/appointment.h"
#include "include/database/load_data.h"
#include "include/account/create_account.h"
#include "include/ui/login_screen.h"
#include "include/ui/user_menu.h"
#include "include/ui/admin_menu.h"
#include "include/auth/username.h"
#include "include/io.h"

// Every database (patient and appointment) starts with room for this many
// records before it needs its first Database_Reallocate.
static const u32 InitialDatabaseCapacity = 10;

typedef enum {
    AUTH_FAILED,
    AUTH_PATIENT,
    AUTH_ADMIN,
    AUTH_EXIT,
} AuthStatus;

AuthStatus Login_Loop(PatientDatabase* database, Patient** user);

// NOTE: main's return type stays plain `int` on purpose - the C runtime that
// calls into this program (crt0/_start) requires exactly `int main(void)`,
// it's not something our code gets to redefine.
int main() {
    PatientDatabase patients;
    patients.count = 0;
    patients.capacity = InitialDatabaseCapacity;
    patients.patients = malloc(patients.capacity * sizeof(Patient));

    AppointmentDatabase appointments;
    appointments.count = 0;
    appointments.capacity = InitialDatabaseCapacity;
    appointments.appointments = malloc(appointments.capacity * sizeof(Appointment));

    Database_Load(PatientDataFile, &patients, PATIENT_TYPE);
    Database_Load(AppointmentDataFile, &appointments, APPOINTMENT_TYPE);

    printf("Starting Clinic Management System...\n");
    sleep(OneSecondDelay);

    Patient* currentUser = NULL;
    AuthStatus status = Login_Loop(&patients, &currentUser);

    if (status == AUTH_PATIENT) {
        UserMenu_Loop(currentUser, &appointments);

    } else if (status == AUTH_ADMIN) {
        AdminMenu_Loop(&patients, &appointments);
    }

    free(patients.patients);
    free(appointments.appointments);

    return 0;
}

AuthStatus Login_Loop(PatientDatabase* database, Patient** user) {
    s32 choice;

    while (1) {
        LoginScreen_Show();

        if (scanf("%ld", &choice) != 1) {
            Io_FlushStdin();
            continue;
        }
        Io_FlushStdin();

        switch (choice) {
            case 1: {
                UsernameLoginResult result = Username_HandleLogin(database, user);

                if (result == USERNAME_LOGIN_PATIENT) {
                    printf("Login successful!\n");
                    return AUTH_PATIENT;

                } else if (result == USERNAME_LOGIN_FAILED) {
                    printf("Login failed\n");

                } else if (result == USERNAME_LOGIN_ADMIN) {
                    printf("Admin login successful!\n");
                    return AUTH_ADMIN;
                }
                break;
            }
            case 2:
                Account_Create(database);
                break;

            case 3:
                printf("Goodbye!\n");
                return AUTH_EXIT;

            default:
                printf("Invalid choice. Try again.\n");
                break;
        }
    }
}
