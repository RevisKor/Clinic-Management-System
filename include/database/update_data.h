#ifndef UPDATE_DATA_H
#define UPDATE_DATA_H

#include "../common.h"

// Appends a single new record to file without touching the rest of it.
void Database_Add(const u8* file, void* entry, DatabaseType type);

// Rewrites file from scratch with every record currently in databasePtr.
// Used after an in-memory delete/cancel, where the file needs to end up
// matching the (now shorter) in-memory array.
void Database_Update(const u8* file, void* databasePtr, DatabaseType type);

// Removes the record matching id from the in-memory database and persists
// the change to file. Returns 1 if a record was removed, 0 if id wasn't found.
s32 Database_Delete(const u8* file, void* databasePtr, DatabaseType type, s32 id);

#endif // UPDATE_DATA_H
