#ifndef CANCEL_APPOINTMENT_H
#define CANCEL_APPOINTMENT_H

#include "../common.h"
#include "../domain/appointment.h"
#include "../database/update_data.h"

// Prints only the appointments belonging to patientId, numbered so they can
// be picked by number. Returns how many were printed, so the caller knows
// the valid selection range.
s32 Appointment_PrintUserAppointments(const AppointmentDatabase* database, s32 patientId);

// Removes one specific appointment (matched by patientId + date + time) and
// rewrites the data file to match. Unlike Database_Delete, this targets an
// exact booking instead of "the first appointment for this patient".
// Returns 1 if cancelled, 0 if no matching appointment was found.
s32 Appointment_Cancel(AppointmentDatabase* database, const u8* file, s32 patientId, const u8* date, const u8* time);

// selection is 1-indexed and refers to the position in the patient's OWN
// list (as printed by Appointment_PrintUserAppointments), not the raw index
// in the full database. Looks up the matching date/time, then hands off to
// Appointment_Cancel to do the actual removal.
s32 Appointment_CancelByNumber(AppointmentDatabase* database, const u8* file, s32 patientId, s32 selection);

// Admin variant: index is the raw 1-indexed row number as shown by
// AdminMenu_PrintAppointmentDatabase (not filtered to one patient, since the
// admin can see and cancel anyone's appointment).
s32 Appointment_CancelByIndex(AppointmentDatabase* database, const u8* file, s32 index);

#endif // CANCEL_APPOINTMENT_H
