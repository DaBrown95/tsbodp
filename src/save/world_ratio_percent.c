#include "save_world_display.h"

int save_world_ratio_percent(int numerator, int denominator)
{
    return display_bios_div((int)((unsigned int)numerator * 100), denominator);
}
