#ifndef DISPLAY_MENU_EFFECTS_H
#define DISPLAY_MENU_EFFECTS_H
#include "resource_condition_entries.h"
#include "resource_conditions.h"

/* Role-specific view at the shared catalog/game-state base. These accesses do
 * not establish a complete game-state layout or actor-entry bounds. */
struct DisplayMenuAwardState {
    unsigned char unknown_00[0xe5], staged, group_count, unknown_e7[9];
    struct ConditionActorEntries *entries;
};
extern struct DisplayMenuAwardState g_display_menu_award_state;
extern unsigned int g_display_menu_once_mask;
extern unsigned char g_frame_actor_social_probe[];
int frame_read_signed_parameter(const void *, unsigned int);
int frame_add_game_value(int);
int actor_entry_find_capacity(struct ConditionActorEntries *, int);
void resource_set_triple(unsigned int, unsigned int, unsigned int);
void display_menu_resolve_selected_kind(unsigned int, int);
void display_menu_show_change(unsigned int);
#endif
