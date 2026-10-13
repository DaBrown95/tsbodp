#include "scene_environment.h"
void scene_clear_retained_display(void)
{
 if(g_game_flags&8){
  g_game_flags&=~8u;
  frame_restore_primary_objects();
  display_release_object_list(&g_frame_primary_list);scene_stage_0802eb9c();
  frame_clear_transient_effects();frame_clear_render_effects();
  g_audio_control.flags&=~9;
  frame_destroy_map_registration(g_frame_registration);g_frame_registration=0;
  background_animation_reset();frame_release_map_resources();
 }
}
