#include "display_time.h"

unsigned int display_time_add(struct DisplayTimeRecord *time,
                              const struct DisplayTimeRecord *delta)
{
    unsigned int changes = 0;
    unsigned char seconds, minutes, hours;
    time->tick += delta->tick;
    if (time->tick < 0) {
        do {
            time->tick += 30;
            time->second--;
            changes |= 1;
        } while (time->tick < 0);
        seconds = delta->second;
        minutes = delta->minute;
        hours = delta->hour;
    } else {
        seconds = delta->second;
        minutes = delta->minute;
        hours = delta->hour;
        if (time->tick > 29) {
            do {
                time->tick -= 30;
                time->second++;
                changes |= 1;
            } while (time->tick > 29);
        }
    }
    {
        unsigned int value = (unsigned char)time->second;
        value += seconds;
        time->second = value;
    }
    if (time->second < 0) {
        do {
            time->second += 60;
            time->minute--;
            changes |= 2;
        } while (time->second < 0);
    } else if (time->second > 59) {
        do {
            time->second -= 60;
            time->minute++;
            changes |= 2;
        } while (time->second > 59);
    }
    {
        unsigned int value = (unsigned char)time->minute;
        value += minutes;
        time->minute = value;
    }
    if (time->minute < 0) {
        do {
            time->minute += 60;
            time->hour--;
            changes |= 4;
        } while (time->minute < 0);
    } else if (time->minute > 59) {
        do {
            time->minute -= 60;
            time->hour++;
            changes |= 4;
        } while (time->minute > 59);
    }
    {
        /* Short-lived current-hour sum; no constrained value crosses a call. */
        register unsigned int value asm("r1") = (unsigned char)time->hour;
        value += hours;
        time->hour = value;
    }
    if (time->hour < 0) {
        do {
            time->hour += 24;
            time->day--;
            changes |= 8;
        } while (time->hour < 0);
    } else if (time->hour > 23) {
        do {
            time->hour -= 24;
            time->day++;
            changes |= 8;
        } while (time->hour > 23);
    }
    return changes;
}
asm(".align 2, 0");
