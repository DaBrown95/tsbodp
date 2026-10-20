#include "scene_link_entry_setup.h"
#include "scene_link_entry_quantities.h"
#include "frame_actor_relation.h"
#include "save_world_display.h"

void scene_link_entry_refresh_offers(void)
{
    struct SceneLinkEffectOffer *record;
    unsigned int i, offer_index;
    struct SceneLinkEffectState *state;

    g_link_offer_adjustment_timer = 2;
    if (g_display_scene_frame_objects[0]) {
        g_display_scene_frame_objects[0]->unknown_0a =
            g_display_scene_catalog[g_scene_request.scene].id;
        frame_set_variant_state(g_display_scene_frame_objects[0], 58);
        display_text_select_font(0, 0, 0);
        for (i = 0; i < 4; ++i) {
            struct FrameObject *object;
            display_text_number_field_zero(0);
            object = g_display_scene_frame_objects[6 + i];
            display_text_set_object_string(object,
                display_scene_lookup_text(6220));
            frame_set_centered_integer_position(
                g_display_scene_frame_objects[6 + i],
                (g_scene_link_entry_captions[i].x + 1) * 8,
                (g_scene_link_entry_captions[i].y * 524288 - 131072) >> 16);
        }
        display_text_set_background_control(g_scene_link_entry_text_control);
    }
    state = &g_link_entry_effect_state;
    offer_index = 0;
    do {
        record = &state->records[offer_index];
        record->count = 0;
        if (record->kind != 42) {
            int base_value;
            int category;
            unsigned short percent;

            base_value =
                (int)g_display_scene_catalog[g_scene_request.scene].number_value;
            category = (signed char)
                g_frame_actor_greetings[record->kind].unknown_26[0];
            percent = (unsigned short)frame_random_range(
                g_scene_link_offer_percent_first[category],
                g_scene_link_offer_percent_last[category]);
            state->records[offer_index].limit = (int)((unsigned int)
                save_world_scale_percent(base_value, percent) << 16);
            base_value =
                (int)g_display_scene_catalog[g_scene_request.scene].number_value;
            percent = (unsigned short)frame_random_range(1,
                g_scene_link_offer_percent_first[(signed char)
                    g_frame_actor_greetings[record->kind].unknown_26[0]]);
            state->records[offer_index].storage08.word08 = (unsigned int)
                save_world_scale_percent(base_value, percent) << 16;
            record->phase = 0;
            state->records[offer_index].cost = 0;
        } else {
            struct LinkEntryGameState *game = &g_link_entry_game_state;
            int limit = save_world_scale_percent(
                (int)g_display_scene_catalog[g_scene_request.scene].number_value,
                150);
            if (game->amount < limit) {
                state->records[offer_index].limit =
                    (int)((unsigned int)game->amount << 16);
            } else {
                state->records[offer_index].limit = (int)((unsigned int)save_world_scale_percent(
                    (int)g_display_scene_catalog[
                        g_scene_request.scene].number_value, 150) << 16);
            }
            state->records[offer_index].cost = 0;
            record->countdown = 2;
        }
    } while (&state->records[++offer_index] <= &state->records[3]);
    display_time_copy(&g_display_countdown, &g_scene_link_offer_countdown);
    display_fill_background_constant_rectangle(1, 9, 0, 21, 14, 0);
    display_fill_background_constant_rectangle(0, 9, 0, 21, 14, 0);
    g_link_entry_effect_state.multiplier = (int)((unsigned int)
        save_world_scale_percent(
            (int)g_display_scene_catalog[g_scene_request.scene].number_value,
            150) << 16);
    g_link_entry_effect_state.multiplier =
        display_bios_div(g_link_entry_effect_state.multiplier, 96);
    g_link_entry_effect_state.selected = 0;
}
