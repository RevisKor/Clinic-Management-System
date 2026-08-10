#ifndef APPOINTMENT_H
#define APPOINTMENT_H

#include "../common.h"

typedef struct {
    s32 patientId;

    u8 date[11]; // DD/MM/YYYY
    u8 time[6];  // HH:MM
} Appointment;

// Growable array of appointments, backing store for the in-memory
// appointment table (mirrors data/Appointments.txt).
typedef struct {
    Appointment* appointments;
    u32 count;
    u32 capacity;
} AppointmentDatabase;

#endif // APPOINTMENT_H
