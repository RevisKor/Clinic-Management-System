#ifndef USER_MENU_H
#define USER_MENU_H

#include "../common.h"
#include "../domain/patient.h"
#include "../appointment/schedule_appointment.h"
#include "../appointment/cancel_appointment.h"

// Prints the patient menu (schedule / cancel / log out).
void UserMenu_Show(void);

// Runs the patient menu until the patient logs out.
void UserMenu_Loop(Patient* currentPatient, AppointmentDatabase* appointmentDatabase);

#endif // USER_MENU_H
