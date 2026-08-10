#ifndef IO_H
#define IO_H

#include "common.h"

// Discards any leftover characters up to and including the next newline.
// Call this after any scanf() so a stray newline (or garbage the format
// specifier rejected) doesn't get read as the next prompt's input.
void Io_FlushStdin(void);

#endif // IO_H
