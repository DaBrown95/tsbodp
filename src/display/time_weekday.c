#include "display_time.h"

short display_time_weekday(const struct DisplayTimeRecord *time)
{
    return time->day % 7;
}
