#include "scene_default_menu.h"

void scene_default_menu_enter_slots(void)
{
    if (!g_scene_request.unknown_10) {
        unsigned char slot;

        display_fill_background_constant_rectangle(0, 4, 16, 22, 2, 0);
        scene_default_menu_prepare_background();
        for (slot = 0; slot < 4; ++slot) {
            unsigned int color;
            unsigned int position, x, y;
            const char *text;

            if (slot == g_scene_request.scene)
                color = 3;
            else {
                unsigned char enabled = g_scene_default_menu_options[slot];

                color = 12;
                if (enabled)
                    color = 0;
            }
            position = (unsigned int)slot * 16;
            x = (position - slot) * 2 + 21;
            y = position + 91;
            text = display_scene_lookup_text(slot + 13);
            display_text_select_font(3, color, -1);
            display_text_draw_line(x, 120, y, text, 1);
        }
    }
    if (audio_game_sample_active(g_scene_default_menu_cue_handle))
        audio_game_stop_sample(g_scene_default_menu_cue_handle);
    g_scene_default_menu_cue_handle = audio_play_animation_cue(1);
}
