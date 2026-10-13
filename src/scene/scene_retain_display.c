#include "scene_environment.h"
void scene_retain_display(void)
{
 background_animation_force_reload();scene_stop_actor_speed_cue();frame_snapshot_map_vram();
 if(!(g_game_flags&0x20000)){frame_retain_primary_objects();g_game_flags|=8;}
 g_scene_request.mode=2;
 display_cpu_copy((void *)0x05000200,g_scene_context.palette,256);
}
