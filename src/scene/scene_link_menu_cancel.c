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

void scene_link_menu_cancel(void)
{
    if (g_scene_request.unknown_10 == 1) {
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
    } else if (!(g_link_flags & 0x8000)) {
        if (g_frame_flags & 0x20) {
            g_scene_request.unknown_10 = 2;
            scene_link_menu_draw_status();
        } else {
            resource_submit_scene(1, 2, g_frame_world_id);
        }
    } else {
        audio_play_animation_cue(3);
    }
    audio_play_animation_cue(2);
}
asm(".align 2,0");
