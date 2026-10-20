#include "save_world_display.h"

int save_world_scale_percent(int value, int percent)
{
    return display_bios_div((int)((unsigned int)value * (unsigned short)percent), 100);
}
