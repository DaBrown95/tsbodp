#include "scene_link_entry_setup.h"
#include "scene_link_offer_effects.h"
#include "input.h"
#include "frame_actor_relation.h"
#include "display_menu_relation.h"

#define offers (g_link_entry_effect_state.records)

void scene_link_entry_step_offers(void)
{
    int minimum = 99999999;
    int index;

    if (--g_link_offer_adjustment_timer == -1) {
        for (index = 1; index < 4; ++index) {
            int other;
            for (other = 0; other < 4; ++other) {
                if (other != index) {
                    int difference = offers[index].count - offers[other].count;
                    if (difference < minimum)
                        minimum = difference;
                }
            }
            if (minimum > g_link_offer_difference_limits[
                    (signed char)g_frame_actor_greetings[offers[index].kind].unknown_26[0]
                ][1]) {
                --offers[index].count;
            } else {
                g_link_offer_adjustments[g_display_menu_relation_traits[
                    offers[index].kind].unknown_00[1]](
                        (unsigned char)index, (signed char)minimum);
            }
        }
        g_link_offer_adjustment_timer = 2;
    }

    {
    unsigned short previous_countdown = offers[0].countdown--;
    if (previous_countdown == 0) {
        int change;
        unsigned int buttons;
        offers[0].countdown = 2;
        change = 0;
        buttons = g_input_current[g_input_config.local_player];
        if (buttons & 0xf0) {
            int count, next_count, multiplier, required, limit;
            if (buttons & 0x40) {
                if (offers[0].count <= 95) {
                    change = 1;
                    audio_play_animation_cue(14);
                }
            } else {
                register unsigned int decrement_pressed asm("r0") =
                    buttons & 0x80;
                if (decrement_pressed) {
                    if (offers[0].count) {
                        change = -1;
                        audio_play_animation_cue(14);
                    }
                }
            }
            count = offers[0].count;
            next_count = count + change;
            multiplier = g_link_entry_effect_state.multiplier;
            required = next_count * multiplier;
            limit = offers[0].limit;
            if (required <= limit) {
                offers[0].count = next_count;
                offers[0].cost = 0;
            } else {
                int remainder = limit - count * multiplier;
                if (remainder > 0)
                    offers[0].cost = remainder;
            }
        }
    }

    }
    for (index = 0; index < 4; ++index) {
        int multiplier = g_link_entry_effect_state.multiplier;
        int total = offers[index].count * multiplier + offers[index].cost;
        int selected = g_link_entry_effect_state.selected;
        const unsigned char *cost_column =
            (const unsigned char *)&g_link_entry_effect_state + 12;
        if (offers[selected].count * multiplier +
                *(const int *)(cost_column + selected * 24) < total)
            g_link_entry_effect_state.selected = index;
    }
}
