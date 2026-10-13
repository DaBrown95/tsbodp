#include "display_menu_results.h"

void display_menu_draw_secondary_result(int variant)
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
    if (menu->definition != 7 || (unsigned int)frame_read_signed_parameter(
            g_frame_actor_social_probe, 4) <= 3)
        text = definitions[menu->definition].text_ids[5];
    else
        text = 2241;
    text += 1 + g_display_menu_state.codes[g_display_scene_request_state.scene];
    display_menu_draw_scrolling_text(display_scene_lookup_text(text));
}

asm(".align 2, 0");
