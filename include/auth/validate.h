#ifndef VALIDATE_H
#define VALIDATE_H

#include "../common.h"

// Prompts with displayPrompt until the user enters a value between
// minimumAllowedLength and maximumAllowedLength characters (and, if
// fieldIdentifier is "password", one that also passes Validate_Password).
// The accepted value is copied into *destinationBuffer.
void Validate_CheckInputLength(const u8* displayPrompt, const u8* fieldIdentifier, u8** destinationBuffer, s32 minimumAllowedLength, s32 maximumAllowedLength);

// Returns 1 if password has at least one uppercase letter, one lowercase
// letter, one digit, and one punctuation character; prints which
// requirements are missing and returns 0 otherwise.
s32 Validate_Password(const u8* password);

#endif // VALIDATE_H
