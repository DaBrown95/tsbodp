#include "scene_relation_grid.h"
void scene_relation_grid_step(void)
{
 if(g_input_pressed[g_input_config.local_player]&240){
  if(g_input_local_pressed[g_input_config.local_player]&128){
   if(g_scene_request.scene<=2)g_scene_request.scene+=3;
  }else if(g_input_local_pressed[g_input_config.local_player]&64){
   if(g_scene_request.scene>2)g_scene_request.scene-=3;
  }
  if(g_input_local_pressed[g_input_config.local_player]&32){
   if(g_scene_request.scene==0||g_scene_request.scene==3){
    if(g_scene_request.parameter){
     g_scene_request.parameter--;
     scene_relation_grid_refresh_entries();
     if(g_scene_request.parameter==0)g_display_scene_frame_objects[7]->flags&=~1u;
     g_display_scene_frame_objects[8]->flags|=1;
    }
   }else g_scene_request.scene--;
  }else if(g_input_local_pressed[g_input_config.local_player]&16){
   if(g_scene_request.scene==2||g_scene_request.scene==5){
    if(g_scene_request.parameter<=8){
     g_scene_request.parameter++;
     scene_relation_grid_refresh_entries();
     if(g_scene_request.parameter==9)g_display_scene_frame_objects[8]->flags&=~1u;
     g_display_scene_frame_objects[7]->flags|=1;
    }
   }else g_scene_request.scene++;
  }
  g_display_scene_frame_objects[9]->id=g_scene_request.scene+95;
  frame_set_variant_state(g_display_scene_frame_objects[9],58);
  scene_relation_grid_draw_detail();
  audio_play_animation_cue(0);
 }
 if(g_input_local_pressed[g_input_config.local_player]&256){
  g_scene_link_catalog_world.requested_kind=16;
  scene_submit_default_request(16);
  audio_play_animation_cue(4);
 }else if(g_input_local_pressed[g_input_config.local_player]&512){
  g_scene_link_catalog_world.requested_kind=14;
  scene_submit_default_request(14);
  audio_play_animation_cue(4);
 }else if(g_input_pressed[g_input_config.local_player]&10){
  resource_submit_scene(1,2,g_scene_id);
  audio_play_animation_cue(2);
 }
}
asm(".align 2,0");
