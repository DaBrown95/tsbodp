#include "scene_link_menu_actions.h"
#include "input.h"
static inline void draw_row(unsigned int row, unsigned int selected)
{
    struct SceneRequest *context = &g_scene_request;
    unsigned int color = 0;
    register unsigned int mode asm("r6");
    unsigned int tile;
    int y;
    const char *text;
    if (row == selected)
        color = 3;
    display_text_select_font(3, color, 0);
    mode = context->unknown_10;
    if (mode == 1) {
        tile = (row + 1) * 64 + 1;
        y = row * 22 + 44;
        text = display_scene_lookup_text(row + 210);
        display_text_draw_line(tile, 120, y, text, mode);
    } else {
        int x;
        tile = row * 64 + 1;
        x = 120;
        if (!(g_frame_flags & 0x20) && !(g_link_flags & 0x8000))
            y = row * 22 + 28;
        else
            y = row * 22 + 64;
        text = display_scene_lookup_text(row + 213);
        display_text_draw_line(tile, x, y, text, 1);
    }
}

void scene_link_menu_change_row(void)
{
    unsigned int old, row;
    if (g_scene_request.unknown_10 == 1) {
        old = g_scene_request.parameter;
        g_scene_request.parameter = input_step_local_vertical_pressed(
            &g_scene_request.parameter, 0, 1, 1, g_input_config.local_player);
        draw_row(old, g_scene_request.parameter);
        row = g_scene_request.parameter;
        draw_row(row, row);
    } else {
        old = g_scene_request.scene;
        g_scene_request.scene = input_step_local_vertical_pressed(
            &g_scene_request.scene, 0, 5, 1, g_input_config.local_player);
        draw_row(old, g_scene_request.scene);
        row = g_scene_request.scene;
        draw_row(row, row);
        {
            unsigned int position_row = g_scene_request.scene;
            if (position_row <= 5)
                frame_set_position(g_display_scene_frame_objects[0],
                    121 << 16, position_row * (22U << 16) + (33U << 16));
            else
                frame_set_position(g_display_scene_frame_objects[0],
                    121 << 16, 33 << 16);
        }
    }
    audio_play_animation_cue(0);
}
asm(".align 2,0");
