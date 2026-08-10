#ifndef CREATE_ACCOUNT_H
#define CREATE_ACCOUNT_H

#include "../common.h"
#include "../domain/patient.h"
#include "../auth/password.h"
#include "../auth/username.h"
#include "../auth/validate.h"
#include "../auth/date.h"
#include "../hash/hash.h"
#include "../database/load_data.h"
#include "../database/update_data.h"

// Data file every new account is appended to.
static const u8 PatientDataFile[] = "data/Patients.txt";

// Walks the user through picking a unique username, a password meeting
// Validate_Password's requirements, a birthdate, and a gender; adds the new
// patient to database and appends it to PatientDataFile.
void Account_Create(PatientDatabase* database);

// Prompts until the user enters 'M'/'m'/'F'/'f' and writes it into *gender.
void Account_GetGender(u8* gender);

#endif // CREATE_ACCOUNT_H
