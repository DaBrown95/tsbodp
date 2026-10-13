#include "display_time.h"

void display_time_copy_add(const struct DisplayTimeRecord *source,
                           const struct DisplayTimeRecord *delta,
                           struct DisplayTimeRecord *destination)
{
    *destination = *source;
    display_time_add(destination, delta);
}
asm(".align 2, 0");
