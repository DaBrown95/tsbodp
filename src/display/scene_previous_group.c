#include "display_scene_navigation.h"
unsigned char display_scene_previous_group(void)
{
    if (!g_display_scene_request_state.scene)
        return 0;
    if (g_display_scene_request_state.scene == 4)
        g_display_scene_objects[3]->flags |= 1;
    --g_display_scene_request_state.scene;
    if (!g_display_scene_request_state.scene && g_display_scene_objects[0]->id == 0xb1)
        g_display_scene_objects[2]->flags &= ~1;
    display_scene_stage_0800f034(0);
    g_display_scene_byte2 = 0;
    display_scene_stage_0800f478();
    display_scene_redraw_details(0);
    audio_play_animation_cue(0);
    return 1;
}
