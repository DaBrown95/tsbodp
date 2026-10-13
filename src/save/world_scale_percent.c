#include "save_world_display.h"

int save_world_scale_percent(int value, unsigned short percent)
{
    return display_bios_div((int)((unsigned int)value * percent), 100);
}
