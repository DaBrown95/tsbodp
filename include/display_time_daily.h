#ifndef DISPLAY_TIME_DAILY_H
#define DISPLAY_TIME_DAILY_H

#include "display_time.h"
#include "display_menu_relation.h"

struct ActorEntryContext;

/* Access view of the existing world root, not a complete state allocation. */
struct DisplayDailyWorld {
    unsigned char unknown00[8];
    struct DisplayTimeRecord clock;
    unsigned char unknown10[0x440 - 0x10];
    unsigned int stage;
    unsigned char unknown444[0x714 - 0x444];
    unsigned int daily_counters[4];
    unsigned char unknown724[0x741 - 0x724];
    unsigned char counter_a, counter_b, unknown743;
    unsigned short cycle_value;
    signed char cycle;
    unsigned char flag;
};
/* Seventeen accessed bytes; the structure's tail padding proves no allocation. */
struct DisplayHourInterval {
    struct DisplayTimeRecord first, last;
    unsigned char enabled;
};
extern struct DisplayDailyWorld g_display_daily_world;
extern struct DisplayHourInterval g_display_hour_interval;

void display_time_reset_hour_interval(void);
void display_time_day_event(void);

void display_time_add_cycle_value(void);
void display_time_reset_daily_counters(void);
void display_menu_relax_relation_values(struct DisplayMenuRelationValues *);
/* Original dependency remains unconverted in the matching build. */
void display_time_weekly_entries(struct ActorEntryContext *);

/* Existing providers; declarations preserve their established ABI. */
void *display_fill_bytes(void *, int, unsigned int);
void actor_entry_reset_values(struct ActorEntryContext *);

#endif
