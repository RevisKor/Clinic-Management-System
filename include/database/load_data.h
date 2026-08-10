#ifndef LOAD_DATA_H
#define LOAD_DATA_H

#include "../common.h"

// Frees whatever the failed database had already allocated, then terminates
// the process. Called when a realloc() for growing a database fails - at
// that point there's no safe way to keep running, so we clean up and exit
// rather than continue with a database in an unknown state.
void Database_HandleAllocationFailure(void* databasePtr, DatabaseType type);

// Doubles a database's capacity in place, exiting via
// Database_HandleAllocationFailure if the underlying realloc() fails.
void Database_Reallocate(void* databasePtr, DatabaseType type);

// Loads every record from file into databasePtr, growing it as needed.
// Exits with FILE_NOT_FOUND_ERROR if the file can't be opened - the project
// expects the data files to already exist (see data/).
void Database_Load(const u8* file, void* databasePtr, DatabaseType type);

#endif // LOAD_DATA_H
