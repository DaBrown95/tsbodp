#include "save_world_display.h"

int save_world_scale_gauge(short value, unsigned short maximum,
                           unsigned char steps)
{
    int ratio;
    int result;
    if (value > 0) {
        ratio = save_world_ratio_percent(value, maximum);
        result = save_world_scale_percent(steps + 1, (unsigned short)ratio);
        if (result > steps)
            result = steps;
        else if (result < 0)
            result = 0;
    } else {
        result = 0;
    }
    return result;
}
