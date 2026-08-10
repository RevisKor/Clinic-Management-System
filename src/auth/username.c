#include "../../include/auth/username.h"
#include "../../include/io.h"

UsernameLoginResult Username_HandleLogin(PatientDatabase* database, Patient** patient) {
    u8 username[65];
    s32 attempts = 3;

    while (attempts > 0) {
        attempts--;

        printf("Enter your username: ");
        scanf("%64s", (char*) username);
        Io_FlushStdin();

        if (strcmp((const char*) username, (const char*) AdminUsername) == 0) {
            if (Password_SignIn((const u8*) "admin", AdminPasswordHash)) {
                return USERNAME_LOGIN_FAILED;
            } else {
                return USERNAME_LOGIN_ADMIN;
            }
        }

        for (u32 index = 0; index < database->count; index++) {
            if (strcmp((const char*) username, (const char*) database->patients[index].username) == 0) {

                if (Password_SignIn((const u8*) "account", database->patients[index].passwordHash)) {
                    return USERNAME_LOGIN_FAILED;
                } else {
                    *patient = &(database->patients[index]);
                    return USERNAME_LOGIN_PATIENT;
                }
            }
        }

        printf("Account not found, please enter a correct username\n");
        sleep(OneSecondDelay);
    }

    printf("Couldn't find the account in the database ...\n");
    sleep(OneSecondDelay);
    printf("Please consider creating an account\n");
    sleep(OneSecondDelay);
    printf("Exiting to login screen ...\n");

    return USERNAME_LOGIN_FAILED;
}
