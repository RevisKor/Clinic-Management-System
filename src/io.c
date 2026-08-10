#include "../include/io.h"

void Io_FlushStdin(void) {
    s32 character;
    while ((character = getchar()) != '\n' && character != EOF);
}
