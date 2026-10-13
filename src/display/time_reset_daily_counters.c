#include "display_time_daily.h"

void display_time_reset_daily_counters(void)
{
    g_display_daily_world.daily_flag_words[0] = 0;
    g_display_daily_world.daily_flag_words[1] = 0;
    g_display_daily_world.daily_flag_words[2] = 0;
    g_display_daily_world.daily_flag_words[3] = 0;
}
asm(".align 2, 0");
