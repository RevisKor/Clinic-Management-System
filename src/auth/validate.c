#include "../../include/auth/validate.h"
#include "../../include/io.h"

void Validate_CheckInputLength(const u8* displayPrompt, const u8* fieldIdentifier, u8** destinationBuffer, s32 minimumAllowedLength, s32 maximumAllowedLength) {
    u8 inputBuffer[256] = "";
    s32 inputIsValid = 0;

    do {
        printf("%s", (const char*) displayPrompt);

        if (scanf(" %255s", (char*) inputBuffer) != 1) {
            Io_FlushStdin();
            printf("Invalid input. Please try again.\n");
            sleep(OneSecondDelay);
            continue;
        }

        Io_FlushStdin();

        s32 currentInputLength = strlen((const char*) inputBuffer);

        if (currentInputLength < minimumAllowedLength) {
            printf("%s too short!\n", (const char*) fieldIdentifier);
            sleep(OneSecondDelay);
            continue;
        }

        if (currentInputLength > maximumAllowedLength) {
            printf("%s too long!\n", (const char*) fieldIdentifier);
            sleep(OneSecondDelay);
            continue;
        }

        if (strcmp((const char*) fieldIdentifier, "password") == 0 && !Validate_Password(inputBuffer)) {
            sleep(OneSecondDelay);
            printf("Password doesn't meet the safety criteria\n");
            sleep(OneSecondDelay);
            printf("Try again\n");
            sleep(OneSecondDelay);
            continue;
        }

        inputIsValid = 1;

    } while (!inputIsValid);

    strcpy((char*) *destinationBuffer, (const char*) inputBuffer);
}

s32 Validate_Password(const u8* password) {
    s32 hasUppercaseLetter = 0, hasLowercaseLetter = 0, hasNumericDigit = 0, hasSpecialCharacter = 0;
    s32 passwordLength = strlen((const char*) password);

    for (s32 characterIndex = 0; characterIndex < passwordLength; characterIndex++) {
        if (isupper(password[characterIndex])) {
            hasUppercaseLetter = 1;
        }
        if (islower(password[characterIndex])) {
            hasLowercaseLetter = 1;
        }
        if (isdigit(password[characterIndex])) {
            hasNumericDigit = 1;
        }
        if (ispunct(password[characterIndex])) {
            hasSpecialCharacter = 1;
        }
    }

    s32 totalMissingRequirements = 0;
    if (!hasUppercaseLetter)   { printf("Password must contain an uppercase letter\n"); totalMissingRequirements++; }
    if (!hasLowercaseLetter)   { printf("Password must contain a lowercase letter\n");  totalMissingRequirements++; }
    if (!hasNumericDigit)      { printf("Password must contain a digit\n");             totalMissingRequirements++; }
    if (!hasSpecialCharacter)  { printf("Password must contain a special character\n"); totalMissingRequirements++; }

    return (totalMissingRequirements == 0);
}
