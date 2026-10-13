#include "display_time.h"

unsigned int display_time_equal(const struct DisplayTimeRecord *first,
                                const struct DisplayTimeRecord *second,
                                unsigned int mask)
{
    unsigned int equal = 1;
    if ((mask & 8) && first->day != second->day) equal = 0;
    if ((mask & 4) && first->hour != second->hour) equal = 0;
    if ((mask & 2) && first->minute != second->minute) equal = 0;
    if ((mask & 1) && first->second != second->second) equal = 0;
    if ((mask & 16) && first->tick != second->tick) equal = 0;
    return equal;
}
asm(".align 2, 0");
