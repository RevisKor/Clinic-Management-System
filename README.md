# Clinic Management System

A terminal-based clinic management system written in C. Patients can register,
log in, and book or cancel appointments; an admin account can review the
patient and appointment records and remove entries.

## Building

```
make
```

Produces the `app` executable. Object files are placed under `obj/`, mirroring
the `src/` layout.

Other targets:

```
make run       # build (if needed) and run ./app
make rebuild   # clean then build
make clean     # remove obj/ and the app binary
```

## Running

The program expects to be run from the project root, since it reads and
writes `data/Patients.txt` and `data/Appointments.txt` using relative paths.

```
./app
```

## Project layout

```
include/          public headers, mirrors src/
  types/           fixed-width integer typedefs
  domain/          core data types (Patient, Appointment, and their databases)
  database/        loading/saving the on-disk record files
  auth/            login, date/time input, and input validation
  appointment/      scheduling and cancelling appointments
  hash/            SHA-256 password hashing
  ui/              menu screens and the loops that drive them
  account/         account creation

src/               mirrors include/, one .c per header
data/              flat-file record storage
main.c             program entry point and the login loop
```

## Notes

* Passwords are hashed with a from-scratch SHA-256 implementation before
  they're stored or compared; plaintext passwords are never written to disk.
* The admin account is a fixed username/password pair, not a row in the
  patient database.
* Patient and appointment records are kept as flat, space-delimited text
  files and are fully rewritten on any update or delete.

---

This project was designed and implemented by **Yahia Shahin**. After
completing the majority of the code manually, AI was used as a development
assistant to help debug issues, improve readability, suggest clearer names,
and restructure the project to a consistent, documented coding standard.
