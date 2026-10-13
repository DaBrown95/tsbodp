#include "display_time.h"

unsigned int display_time_compare(const struct DisplayTimeRecord *first,
                                  const struct DisplayTimeRecord *second,
                                  unsigned int mask)
{
    if ((mask & 8) && first->day != second->day) {
        if (first->day < second->day) return 1;
        else return 2;
    }
    if ((mask & 4) && first->hour != second->hour) {
        if (first->hour < second->hour) return 1;
        else return 2;
    }
    if ((mask & 2) && first->minute != second->minute) {
        if (first->minute < second->minute) return 1;
        else return 2;
    }
    if ((mask & 1) && first->second != second->second) {
        if (first->second < second->second) return 1;
        else return 2;
    }
    return 0;
}
asm(".align 2, 0");
