#include "../../include/account/create_account.h"
#include "../../include/io.h"

// Patient IDs start at 100 (rather than 0) purely so they read as account
// numbers instead of raw array indices.
static const u32 PatientIdOffset = 100;

void Account_Create(PatientDatabase* database) {
    u8 username[65] = "";
    u8 password[65] = "";
    u8 passwordHash[65] = "";

    u8* usernamePtr = username;
    u8* passwordPtr = password;

    s32 isUnique = 0;

    u8 gender;
    u8 birthDate[11] = {0};

    printf("===== Account Creation =====\n");

    // Loop until the user enters a unique, valid username.
    while (!isUnique) {
        Validate_CheckInputLength((const u8*) "Enter your desired username: ", (const u8*) "Username", &usernamePtr, 4, 50);

        isUnique = 1;

        for (u32 index = 0; index < database->count; index++) {
            if (strcmp((const char*) username, (const char*) database->patients[index].username) == 0) {
                printf("Username taken! Try again\n");
                sleep(OneSecondDelay);
                isUnique = 0;
                break;
            }
        }
    }

    Validate_CheckInputLength((const u8*) "Enter your desired password: ", (const u8*) "password", &passwordPtr, 8, 16);
    Hash_Password(passwordPtr, passwordHash);

    Date_GetDate((const u8*) "Enter your birthdate", birthDate);
    Account_GetGender(&gender);

    if (database->count >= database->capacity) {
        Database_Reallocate(database, PATIENT_TYPE);
    }

    u32 index = database->count;

    database->patients[index].patientId = index + PatientIdOffset;
    database->patients[index].gender = gender;
    strcpy((char*) database->patients[index].birthDate, (const char*) birthDate);
    strcpy((char*) database->patients[index].username, (const char*) username);
    strcpy((char*) database->patients[index].passwordHash, (const char*) passwordHash);

    database->count++;

    printf("\n====================================\n");
    printf("| Patient ID: %ld\n", database->patients[index].patientId);
    printf("| Username: %s\n", (const char*) usernamePtr);
    printf("| Password: %s\n", (const char*) passwordPtr);
    printf("====================================\n");
    printf("These are your username and password. Memorize them and do not share them!\n\n");

    Io_FlushStdin();

    printf("Press Enter to continue... ");
    getchar();

    Database_Add(PatientDataFile, &(database->patients[index]), PATIENT_TYPE);
}

void Account_GetGender(u8* gender) {
    u8 inputBuffer;

    do {
        printf("What is your gender? (M / F): ");
        scanf(" %c", (char*) &inputBuffer);
        Io_FlushStdin();

    } while (inputBuffer != 'M' && inputBuffer != 'm' && inputBuffer != 'F' && inputBuffer != 'f');

    *gender = inputBuffer;
}
