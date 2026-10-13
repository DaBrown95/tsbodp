#include "display_time_daily.h"

void display_time_add_cycle_value(void)
{
    g_display_daily_world.cycle_value += 500;
}
asm(".align 2, 0");
