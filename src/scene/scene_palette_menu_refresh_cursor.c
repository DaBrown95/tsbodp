#include "scene_palette_menu_input.h"
void scene_palette_menu_refresh_cursor(void)
{
    if (g_scene_request.scene == 3) {
        struct FrameObject **objects = g_frame_actor_palette_menu_objects;
        objects[13]->flags &= ~1U;
        objects[14]->flags |= 1;
    } else {
        struct FrameObject **objects = g_frame_actor_palette_menu_objects;
        unsigned int flags = objects[13]->flags;
        if (flags & ~1U) {
            objects[13]->flags = flags | 1;
            objects[14]->flags &= ~1U;
        }
        frame_set_position(objects[13],
            (unsigned int)g_palette_menu_cursor_x[g_scene_request.parameter] << 16,
            (unsigned int)g_palette_menu_cursor_y[g_scene_request.scene] << 16);
    }
    audio_play_animation_cue(0);
}
asm(".align 2,0");
