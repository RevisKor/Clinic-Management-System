#ifndef PASSWORD_H
#define PASSWORD_H

#include "../common.h"
#include "../hash/hash.h"

// Gives the caller 3 attempts to type the password matching
// accountPasswordHash. label is used purely for the prompt text (e.g.
// "account" or "admin") so this one function serves both patient and admin
// sign-in instead of two near-identical copies of the same attempt loop.
// Returns 0 on success, 1 if all attempts are used up.
s32 Password_SignIn(const u8* label, const u8* accountPasswordHash);

#endif // PASSWORD_H
