#include "display_menu_results.h"

void display_menu_draw_primary_result(int variant, unsigned char success)
{
    const struct DisplayMenuResultDescriptor *definitions = g_display_menu_result_descriptors;
    int offset = variant * sizeof(void *);
    struct DisplayMenuState *menu = &g_display_menu_state;
    unsigned short text;
    display_load_background_dma(2, display_menu_result_resource(definitions, menu->definition, offset),
        1 + 182 * (menu->resource_shown & 1), 0, 15, 0);
    menu->resource_shown ^= 1;
    offset += (unsigned int)display_menu_result_cues(definitions, menu->definition);
    audio_play_animation_cue(*(const unsigned int *)offset);
    if (menu->codes[g_display_scene_request_state.scene] != 22) {
        if (menu->definition != 7 || (unsigned int)frame_read_signed_parameter(
                g_frame_actor_social_probe, 4) <= 3)
            text = definitions[menu->definition].text_ids[5];
        else
            text = 2241;
        text += 1 + g_display_menu_state.codes[g_display_scene_request_state.scene];
    } else {
        if (menu->definition != 7 || (unsigned int)frame_read_signed_parameter(
                g_frame_actor_social_probe, 4) <= 3)
            text = definitions[menu->definition].text_ids[5];
        else
            text = 2241;
        if (success == 1) {
            text += g_display_menu_page_text_variants[5];
            g_display_menu_result_actor_selection.actor = g_display_menu_state.definition + 18;
        } else
            text += g_display_menu_page_text_variants[4];
    }
    if (!success || (g_display_menu_state.codes[g_display_scene_request_state.scene] != 3 &&
        g_display_menu_state.codes[g_display_scene_request_state.scene] != 5 &&
        g_display_menu_state.codes[g_display_scene_request_state.scene] != 4)) {
        if (!g_display_menu_state.unknown_28)
            display_menu_show_hint(1);
        display_menu_draw_scrolling_text(display_scene_lookup_text(text));
        display_text_set_background_control(g_display_menu_control0);
    }
}

asm(".align 2, 0");
