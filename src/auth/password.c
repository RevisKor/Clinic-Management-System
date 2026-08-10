#include "../../include/auth/password.h"
#include "../../include/io.h"

s32 Password_SignIn(const u8* label, const u8* accountPasswordHash) {
    s32 attempts = 3, isLoggedIn = 0;
    u8 inputHash[65];

    // Gives the user 3 attempts to enter the correct password.
    while ((attempts > 0) && !isLoggedIn) {
        u8 inputBuffer[65];
        attempts--;

        printf("Please enter the %s password: ", (const char*) label);
        scanf("%64s", (char*) inputBuffer);
        Io_FlushStdin();

        Hash_Password(inputBuffer, inputHash);
        if (strcmp((const char*) inputHash, (const char*) accountPasswordHash) == 0) {
            isLoggedIn = 1;
        }
    }

    if (isLoggedIn) {
        printf("Access granted\n");
        return 0;

    } else {
        printf("Access denied\n");
        printf("Exiting to login screen\n");
        sleep(OneSecondDelay);
        return 1;
    }
}
