#include "scene_default_menu.h"

/* The first member is a text tile word; the second is a vertical position. */
struct DefaultMenuTextPosition { unsigned int tile, y; };

static inline void select_row_font(int value)
{
    unsigned int font;
    int palette;
    int fill;

    font = 3;
    palette = value;
    fill = -1;
    display_text_select_font(font, palette, fill);
}

void scene_default_menu_change_selection(void)
{
    unsigned int style;
    unsigned int color;
    unsigned int position;
    struct DefaultMenuTextPosition point;
    const char *text;

    {
        union { unsigned int row; const char *text; } working;

        working.row = g_scene_request.scene;
        input_step_vertical_pressed(&g_scene_request.scene, 0, 3, 1,
                                    g_input_config.local_player);
        while (!g_scene_default_menu_options[g_scene_request.scene])
            input_step_vertical_pressed(&g_scene_request.scene, 0, 3, 1,
                                        g_input_config.local_player);
        if (working.row == g_scene_request.scene)
            color = 3;
        else {
            unsigned char enabled = g_scene_default_menu_options[working.row];

            color = 12;
            if (enabled)
                color = 0;
        }
        position = working.row * 16;
        point.tile = (position - working.row) * 2 + 21;
        point.y = position + 91;
        working.text = display_scene_lookup_text(working.row + 13);
        select_row_font(color);
        style = 1;
        display_text_draw_line(point.tile, 120, point.y, working.text, style);
    }
    position = g_scene_request.scene * 16;
    point.tile = (position - g_scene_request.scene) * 2 + 21;
    point.y = position + 91;
    text = display_scene_lookup_text(g_scene_request.scene + 13);
    select_row_font(3);
    display_text_draw_line(point.tile, 120, point.y, text, style);
    if (g_scene_request.scene <= 3)
        frame_set_position(g_scene_default_menu_selector, 0x400000,
                           (int)(0x590000u + (g_scene_request.scene << 20)));
    else
        frame_set_position(g_scene_default_menu_selector, 0x400000, 0x590000);
    if (audio_game_sample_active(g_scene_default_menu_cue_handle))
        audio_game_stop_sample(g_scene_default_menu_cue_handle);
    g_scene_default_menu_cue_handle = audio_play_animation_cue(0);
}
