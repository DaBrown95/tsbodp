#include "display_time_daily.h"
#include "frame_random.h"

void display_time_reset_hour_interval(void)
{
    struct DisplayHourInterval *interval = &g_display_hour_interval;
    display_fill_bytes(&interval->first, 0, 8);
    display_fill_bytes(&interval->last, 0, 8);
    if (frame_random_range(0, 99) <= 29) {
        int first, last;
        interval->enabled = 1;
        first = frame_random_range(0, 22);
        last = frame_random_range(first + 1, 22);
        interval->first.hour = first;
        interval->last.hour = last;
    } else {
        interval->enabled = 0;
    }
}
asm(".align 2, 0");
