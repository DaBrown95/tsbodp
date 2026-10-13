#include "display_menu_pages.h"
#include "display_text_fields.h"
#include "audio_game.h"

void display_menu_prepare_choice_text(void)
{
    unsigned int text_id;
    unsigned char result;
    if (g_display_menu_state.definition != 7
        || (unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 4) <= 3)
        text_id = g_frame_actor_greetings[g_display_menu_state.definition].text_ids[5];
    else
        text_id = 2241;
    result = display_menu_prepare_choice(&g_display_menu_selection_state,
        g_display_menu_state.definition,
        (unsigned char *)&g_display_menu_selection_state - 1040);
    if (result) {
        display_text_copy_field_one(display_scene_lookup_text(
            g_display_menu_selection_state.text_kind + 6025));
        display_load_background_dma(2,
            g_frame_actor_greetings[g_display_menu_state.definition].choice_background_resource,
            1 + 182 * (g_display_menu_state.resource_shown & 1), 0, 15, 0);
        g_display_menu_state.resource_shown ^= 1;
        audio_play_animation_cue(
            g_frame_actor_greetings[g_display_menu_state.definition].cue_record[6]);
        display_menu_draw_scrolling_text(display_scene_lookup_text(
            text_id + g_display_menu_page_text_variants[1]));
    } else {
        display_load_background_dma(2,
            g_frame_actor_greetings[g_display_menu_state.definition].background_resource,
            1 + 182 * (g_display_menu_state.resource_shown & 1), 0, 15, 0);
        g_display_menu_state.resource_shown ^= 1;
        audio_play_animation_cue(
            g_frame_actor_greetings[g_display_menu_state.definition].cue_record[2]);
        {
            unsigned int code =
                g_display_menu_state.codes[g_display_scene_request_state.scene];
            code += 1;
            display_menu_draw_scrolling_text(display_scene_lookup_text(code + text_id));
        }
    }
}
asm(".align 2, 0");
