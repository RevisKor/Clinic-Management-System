#ifndef HASH_H
#define HASH_H

#include "../common.h"

// Fixed admin credential pair. The admin account is not a row in the patient
// database, so it needs its own username + password hash (see
// auth/username.c and auth/password.c). The password hash below is
// Hash_Password("Admin@2026") so it can be checked the same way a patient's
// password is, instead of comparing plaintext.
static const u8 AdminUsername[] = "admin";
static const u8 AdminPasswordHash[] = "a36aef5a11c4073fbe60314fc9df530a9d5f986533594d1f5190742ff9e0e408";

// Hashes a NUL-terminated password with SHA-256 and writes the result to
// outputHash as a 64-character lowercase hex string plus terminator.
// outputHash must have room for at least 65 bytes.
void Hash_Password(const u8* password, u8* outputHash);

#endif // HASH_H
