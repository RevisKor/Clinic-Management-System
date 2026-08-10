#ifndef SCHEDULE_APPOINTMENT_H
#define SCHEDULE_APPOINTMENT_H

#include "../common.h"
#include "../domain/patient.h"
#include "../domain/appointment.h"
#include "../auth/date.h"
#include "../database/load_data.h"
#include "../database/update_data.h"

// Data file every new appointment is appended to.
static const u8 AppointmentDataFile[] = "data/Appointments.txt";

static const u8 ClinicOpeningHours[] = "09:00";
static const u8 ClinicClosingHours[] = "17:00";
static const u32 SlotIntervalMinutes = 30;

s32 Appointment_IsSlotTaken(AppointmentDatabase* database, const u8* date, const u8* time);
void Appointment_PrintAvailableTimes(AppointmentDatabase* database, const u8* date);

// Walks the patient through picking a valid, open, unbooked date/time slot,
// then books it for currentPatient and persists it.
void Appointment_Schedule(Patient* currentPatient, AppointmentDatabase* database);

#endif // SCHEDULE_APPOINTMENT_H
