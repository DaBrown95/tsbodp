#ifndef DISPLAY_MENU_RELATION_EVENTS_H
#define DISPLAY_MENU_RELATION_EVENTS_H
#include "display_menu_relation.h"
#include "display_time.h"

/* Partial producer views; the observed ROM/RAM index has no established bound. */
struct DisplayWorldClockSelection {
    unsigned char unknown_00[0x31], row;
};
struct DisplayWorldClockRow {
    unsigned int unknown_00, flags;
    unsigned char unknown_08[48];
};
struct DisplayWorldClockTimers {
    unsigned char unknown_00[0x749], paused, unknown_74a[2];
    int remaining;
};
extern struct DisplayTimeRecord g_display_world_clock;
extern struct DisplayWorldClockSelection g_display_world_clock_selection;
extern struct DisplayWorldClockRow g_display_world_clock_rows[];
extern struct DisplayWorldClockTimers g_display_world_clock_timers;
extern struct DisplayMenuRelationValues g_display_menu_relation_values;

unsigned char display_menu_relation_initialized(void *, unsigned int);
void display_menu_age_relation_delays(void *);
/* Incoming delay is a full word, multiplied by four then narrowed to a byte. */
void display_menu_set_relation_delay(void *, unsigned int, unsigned int);
void display_menu_try_relation_flag(void *, unsigned int);
void display_time_step_world(const struct DisplayTimeRecord *);
/* Unconverted dependency; this caller supplies no explicit arguments. */
void display_time_day_event(void);

#endif
