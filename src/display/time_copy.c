#include "display_time.h"

void display_time_copy(struct DisplayTimeRecord *destination,
                       const struct DisplayTimeRecord *source)
{
    *destination = *source;
}
asm(".align 2, 0");
