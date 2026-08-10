#ifndef COMMON_H
#define COMMON_H

// Standard imports shared by (almost) every module.
#include "types/std_types.h"

#include <ctype.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Which flat-file record a database function is being asked to operate on.
// The database load/update modules are generic over Patient vs. Appointment
// records, so callers pass this instead of duplicating each function per type.
typedef enum {
    PATIENT_TYPE,
    APPOINTMENT_TYPE,
} DatabaseType;

// Process-exit codes for unrecoverable startup/runtime failures.
typedef enum {
    MEMORY_ALLOCATION_ERROR = 1,
    FILE_NOT_FOUND_ERROR,
    INTERNAL_ERROR,
} ErrorStatus;

// Used to pace status messages (e.g. "Booking your appointment...") so the
// user can actually read them instead of the screen flashing past.
static const u32 OneSecondDelay = 1;

#endif // COMMON_H
