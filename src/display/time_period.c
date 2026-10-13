#include "display_time.h"

unsigned int display_time_period(const struct DisplayTimeRecord *time)
{
    int hour = time->hour;
    unsigned int period = 3;
    if (hour > 5) {
        period = 0;
        if (hour > 9) {
            period = 1;
            if (hour > 16) {
                period = 3;
                if (hour <= 19) period = 2;
            }
        }
    }
    return period;
}
asm(".align 2, 0");
