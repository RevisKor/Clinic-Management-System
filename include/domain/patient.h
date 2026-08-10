#ifndef PATIENT_H
#define PATIENT_H

#include "../common.h"

typedef struct {
    u8 username[65];
    s32 patientId;

    u8 passwordHash[65];

    u8 birthDate[11]; // DD/MM/YYYY
    u8 gender;        // 'M' or 'F'
} Patient;

// Growable array of patients, backing store for the in-memory patient table
// (mirrors data/Patients.txt).
typedef struct {
    Patient* patients;
    u32 count;
    u32 capacity;
} PatientDatabase;

#endif // PATIENT_H
