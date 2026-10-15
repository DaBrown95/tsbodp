#include "scene_choice_panel.h"
void scene_choice_panel_begin_close(void)
{
 audio_play_animation_cue(80);
 if(g_actor_scene_request.active==1 && g_actor_scene_request.object) g_actor_scene_request.object->flags&=~1U;
 scene_choice_panel_original_window_end(10);
 g_scene_request.unknown_14=10;
 g_scene_request.unknown_10=3;
}
asm(".align 2,0");
