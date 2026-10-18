#include "scene_link_entry_linked_refresh.h"

void scene_link_entry_refresh_linked_offers(void)
{
    int i;

    if (g_display_scene_frame_objects[0]) {
        g_display_scene_frame_objects[0]->unknown_0a =
            g_display_scene_catalog[g_scene_request.scene].id;
        frame_set_variant_state(g_display_scene_frame_objects[0], 58);
        display_text_select_font(0, 0, 0);
        display_text_set_background_control(g_scene_link_entry_text_control);
    }
    i = 0;
    if (i < g_link_received_join.metadata[0]) {
        const SceneLinkCatalogColumnByte *number_values =
            (const SceneLinkCatalogColumnByte *)(
                (const unsigned char *)&g_display_scene_catalog + 20);
        struct SceneLinkEffectOffer *record = &g_link_entry_effect_state.records[0];
        for (; i < g_link_received_join.metadata[0]; ++i) {
            unsigned int value;

            if (i != g_link_received_join.identifier) {
                record->count = 0;
                value = g_link_received_join.values[i];
            } else {
                record->count = 95;
                __builtin_memcpy(&value,
                    number_values + g_scene_request.scene *
                        sizeof(struct DisplayCatalogItem), sizeof value);
                value = (unsigned int)save_world_scale_percent(
                    (int)value, 200);
            }
            value <<= 16;
            /* Four representation bytes at the actual record's +4 field. */
            __builtin_memcpy((unsigned char *)record + 4,
                             &value, sizeof value);
            record->cost = 0;
            ++record;
        }
    }
    display_time_copy(&g_display_countdown, &g_scene_link_offer_countdown);
    display_fill_background_constant_rectangle(1, 9, 0, 21, 14, 0);
    display_fill_background_constant_rectangle(0, 9, 0, 21, 14, 0);
    g_link_entry_effect_state.multiplier = (int)((unsigned int)
        save_world_scale_percent(
            (int)g_display_scene_catalog[g_scene_request.scene].number_value,
            200) << 16);
    g_link_entry_effect_state.multiplier =
        display_bios_div(g_link_entry_effect_state.multiplier, 96);
    g_link_entry_effect_state.selected = 0;
}
