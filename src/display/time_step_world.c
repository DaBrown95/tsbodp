#include "display_menu_relation_events.h"

void display_time_step_world(const struct DisplayTimeRecord *delta)
{
    struct DisplayTimeRecord *clock = &g_display_world_clock;
    unsigned int changed = display_time_add(clock, delta);
    if (changed != 0) {
        g_display_world_clock_rows[g_display_world_clock_selection.row].flags |= 3;
        if (changed & DISPLAY_TIME_DAY)
            display_time_day_event();
        if (changed & DISPLAY_TIME_HOUR) {
            int hour = clock->hour;
            if (hour == 0 || hour == 6 || hour == 12 || hour == 18)
                display_menu_age_relation_delays(&g_display_menu_relation_values);
        }
        if (g_display_world_clock_timers.remaining >= 0 && (changed & DISPLAY_TIME_MINUTE) &&
            g_display_world_clock_timers.paused == 0)
            --g_display_world_clock_timers.remaining;
    }
}

asm(".align 2, 0");
