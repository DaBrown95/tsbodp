#include "display_scene_navigation.h"
unsigned char display_scene_next_group(void)
{
    if (g_display_scene_request_state.scene == 5)
        return 0;
    if (g_display_scene_request_state.scene == 1)
        g_display_scene_objects[2]->flags |= 1;
    ++g_display_scene_request_state.scene;
    if (g_display_scene_request_state.scene == 5 && g_display_scene_objects[0]->id == 0xb2)
        g_display_scene_objects[3]->flags &= ~1;
    display_scene_stage_0800f034(0);
    g_display_scene_byte2 = 0;
    display_scene_stage_0800f478();
    display_scene_stage_0800ef2c(0);
    audio_play_animation_cue(0);
    return 1;
}
