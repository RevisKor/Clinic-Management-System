#ifndef USERNAME_H
#define USERNAME_H

#include "../common.h"
#include "../domain/patient.h"
#include "password.h"

// Outcome of Username_HandleLogin - named so callers don't have to remember
// what a bare 0/1/2 return code means.
typedef enum {
    USERNAME_LOGIN_FAILED,
    USERNAME_LOGIN_PATIENT,
    USERNAME_LOGIN_ADMIN,
} UsernameLoginResult;

// Prompts for a username, then either runs the admin password check (if the
// username is "admin") or looks it up in database and runs the matching
// patient's password check. On success with a patient account, *patient is
// pointed at that patient's record in database.
UsernameLoginResult Username_HandleLogin(PatientDatabase* database, Patient** patient);

#endif // USERNAME_H
