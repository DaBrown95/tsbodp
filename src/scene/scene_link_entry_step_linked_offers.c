#include "scene_link_entry_setup.h"
#include "scene_link_offer_effects.h"
#include "input.h"

static inline struct SceneLinkEffectOffer *quantity_offer(int index)
{
    return &g_link_entry_effect_state.records[index];
}

static inline int quantity_limit(int index)
{
    const unsigned char *column = (const unsigned char *)&g_link_entry_effect_state + 4;
    return *(const int *)(column + index * 24);
}

static inline void quantity_set_cost(int index, int cost)
{
    int byte_offset = index * 24;
    unsigned char *column = (unsigned char *)&g_link_entry_effect_state + 12;
    *(int *)(column + byte_offset) = cost;
}

void scene_link_entry_step_linked_offers(void)
{
    int change = 0;
    unsigned int buttons = g_input_current[g_link_received_join.identifier];
    int index;

    if (buttons & 0xf0) {
        if (buttons & 0x40) {
            if (g_link_entry_effect_state.records[g_link_received_join.identifier].count <= 95)
                change = 1;
        } else {
            register unsigned int decrement_pressed asm("r0") = buttons & 0x80;
            if (decrement_pressed) {
                if (g_link_entry_effect_state.records[g_link_received_join.identifier].count)
                    change = -1;
            }
        }
        {
            struct SceneLinkEffectOffer *offer =
                quantity_offer(g_link_received_join.identifier);
            int count = offer->count;
            int next_count = count + change;
            int multiplier = g_link_entry_effect_state.multiplier;
            int required = next_count * multiplier;
            int limit = quantity_limit(g_link_received_join.identifier);
            if (required <= limit) {
                offer->count = next_count;
                if (change)
                    audio_play_animation_cue(15);
                quantity_set_cost(g_link_received_join.identifier, 0);
            } else {
                int remainder = limit - count * multiplier;
                if (remainder > 0)
                    quantity_set_cost(g_link_received_join.identifier, remainder);
            }
        }
    }

    for (index = 0; index < g_link_received_join.metadata[0]; ++index) {
        change = 0;
        if (index != g_link_received_join.identifier) {
            unsigned int buttons = g_input_current[index];
            if (buttons & 0xf0) {
                struct SceneLinkEffectOffer *offer;
                int count, next_count, multiplier, required, limit;
                if (buttons & 0x40) {
                    if (g_link_entry_effect_state.records[index].count <= 95)
                        change = 1;
                } else {
                    register unsigned int decrement_pressed asm("r0") = buttons & 0x80;
                    if (decrement_pressed) {
                        if (g_link_entry_effect_state.records[index].count)
                            change = -1;
                    }
                }
                offer = quantity_offer(index);
                count = offer->count;
                next_count = count + change;
                multiplier = g_link_entry_effect_state.multiplier;
                required = next_count * multiplier;
                limit = quantity_limit(index);
                if (required <= limit) {
                    offer->count = next_count;
                    if (change)
                        audio_play_animation_cue(14);
                    quantity_set_cost(index, 0);
                } else {
                    int remainder = limit - count * multiplier;
                    if (remainder > 0)
                        quantity_set_cost(index, remainder);
                }
            }
        }
    }
}
