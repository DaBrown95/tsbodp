#include "scene_link_menu_actions.h"
#include "frame.h"
static inline void draw_row(unsigned int row, unsigned int selected)
{
    struct SceneRequest *context = &g_scene_request;
    unsigned int color = 0;
    unsigned int mode;
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

void scene_link_menu_accept(void)
{
    if (g_scene_request.unknown_10 == 1) {
        if (g_scene_request.parameter) {
            unsigned char row;
            g_scene_request.unknown_10 = 0;
            display_fill_background_constant_rectangle(2, 2, 3, 28, 24, 0);
            row = 0;
            do {
                draw_row(row, g_scene_request.scene);
                ++row;
            } while (row <= 5);
            display_enable_background(1);
            g_display_scene_frame_objects[0]->flags |= 1;
            display_reset_palette_jobs();
        } else {
            scene_submit_default_request(5);
        }
    } else {
        switch (g_scene_request.scene) {
        case 0: scene_submit_default_request(22); break;
        case 1: scene_submit_default_request(18); break;
        case 2: scene_submit_default_request(24); break;
        case 4:
            g_scene_link_menu_selector_word = 11;
            resource_submit_scene(7, 1, 0);
            break;
        case 3:
            resource_submit_scene(6, 0, g_scene_request.unknown_00);
            break;
        case 5:
            g_scene_request.unknown_10 = 1;
            g_scene_request.parameter = 1;
            display_fill_background_constant_rectangle(2, 2, 3, 28, 24, 0);
            display_hide_background(1);
            g_display_scene_frame_objects[0]->flags &= ~1;
            display_text_select_font(1, 0, 0);
            display_text_draw_line(1, 120, 28, display_scene_lookup_text(219), 1);
            {
                unsigned int row = g_scene_request.parameter;
                draw_row(row, row);
            }
            draw_row(0, g_scene_request.parameter);
            display_load_palette_ranges(&g_display_menu_palette_ranges);
            break;
        }
    }
    audio_play_animation_cue(1);
}
asm(".align 2,0");
