#include "display_menu_effects.h"

void display_menu_resolve_selected_kind(unsigned int kind, int quantity)
{
    if (kind == 143) {
        int parameter = frame_read_signed_parameter(g_frame_actor_social_probe, 2);
        int multiplier = 20 * quantity;
        frame_add_game_value(parameter * multiplier + 30);
    } else if (kind == 144) {
        if (!(unsigned char)condition_is_complete(3, 1, 2)) {
            frame_add_game_value(5000);
            resource_set_triple(3, 1, 2);
            --quantity;
        }
        {
            int parameter = frame_read_signed_parameter(g_frame_actor_social_probe, 2);
            int multiplier = 50 * quantity;
            frame_add_game_value(parameter * multiplier);
        }
    } else if (kind == 129) {
        unsigned int total = 0, i = 0;
        const unsigned int *flags = &g_display_menu_once_mask;
        unsigned int one = 1;
        unsigned int mask = *flags;
        do {
            if ((one << i) & mask)
                ++total;
            ++i;
        } while (i <= 23);
        if (total > 9)
            resource_set_triple(2, 3, 3);
    } else if (kind == 118) {
        resource_set_triple(2, 4, 3);
    } else if (kind == 125) {
        struct DisplayMenuAwardState *state = &g_display_menu_award_state;
        unsigned char *staged = &state->staged;
        if (*staged == 255 && actor_entry_find_capacity(state->entries, 125) == -1) {
            *staged = 0;
            resource_set_triple(1, 0, 0);
        }
    } else if (kind == 142) {
        resource_set_triple(0, 0, 1);
    } else if (kind == 130) {
        resource_set_triple(1, 3, 1);
    } else if (kind - 119 <= 4) {
        g_display_menu_award_state.group_count += quantity;
        if (g_display_menu_award_state.group_count > 2)
            resource_set_triple(2, 2, 2);
    } else if (kind == 140) {
        resource_set_triple(3, 0, 1);
    }
}
asm(".align 2, 0");
