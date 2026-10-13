#include "display_time_daily.h"

void display_time_day_event(void)
{
    {
        struct DisplayDailyWorld *state = &g_display_daily_world;
        unsigned char cycle;
        if (state->stage > 1) {
            ++state->counter_a;
            ++state->counter_b;
        }
        cycle = (unsigned char)state->cycle;
        if (state->cycle != -1) {
            state->cycle = cycle - 1;
            if (state->cycle == 0) {
                display_time_add_cycle_value();
                state->cycle = 7;
            }
        }
    }
    {
        struct DisplayDailyWorld *state = &g_display_daily_world;
        struct ActorEntryContext *entries;
        state->flag = 0;
        display_time_reset_daily_counters();
        entries = (struct ActorEntryContext *)((unsigned char *)state + 0xdc);
        actor_entry_reset_values(entries);
        display_menu_relax_relation_values(
            (struct DisplayMenuRelationValues *)((unsigned char *)state + 0x30));
        ((unsigned char *)state)[0x73d] = 0;
        display_time_reset_hour_interval();
        if ((short)(state->clock.day % 7) == 0)
            display_time_weekly_entries(entries);
    }
}
asm(".align 2, 0");
