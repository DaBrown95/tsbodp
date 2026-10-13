#include "display_time.h"

unsigned int display_time_in_range(const struct DisplayTimeRecord *start,
                                   const struct DisplayTimeRecord *end,
                                   const struct DisplayTimeRecord *time,
                                   unsigned int mask)
{
    unsigned int from_start = display_time_compare(time, start, mask);
    unsigned int from_end = display_time_compare(time, end, mask);
    unsigned int ordering = display_time_compare(start, end, mask);
    if ((ordering == 1 && (from_start == 1 || from_end == 2)) ||
        (ordering == 2 && from_start == 1 && from_end == 2)) return 0;
    return 1;
}
asm(".align 2, 0");
