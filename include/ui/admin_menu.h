#ifndef ADMIN_MENU_H
#define ADMIN_MENU_H

#include "../common.h"
#include "../domain/patient.h"
#include "../domain/appointment.h"
#include "../database/update_data.h"
#include "../appointment/cancel_appointment.h"
#include "../appointment/schedule_appointment.h" // AppointmentDataFile
#include "../account/create_account.h"           // PatientDataFile

// Prints the admin menu (view/delete patients and appointments, log out).
void AdminMenu_Show(void);

// Runs the admin menu until the admin logs out.
void AdminMenu_Loop(PatientDatabase* patientDatabase, AppointmentDatabase* appointmentDatabase);

void AdminMenu_PrintPatientDatabase(const PatientDatabase* database);
void AdminMenu_PrintAppointmentDatabase(const AppointmentDatabase* database);

#endif // ADMIN_MENU_H
