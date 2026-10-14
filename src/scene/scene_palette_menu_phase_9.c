#include "scene_palette_menu_selection_transition.h"
void scene_palette_menu_phase_9(void) {
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==30) {
  struct FrameObject **objects;
  display_set_window_rectangle(1,241*65536,0,240*65536,160*65536);
  display_configure_window(1,63,59);
  display_set_background_scroll_target(2,0,0,15);
  objects=g_frame_actor_palette_menu_objects;
  objects[7]->id=28;
  ((struct FrameActorObject*)objects[7])->need_timer=15;
  frame_set_variant_state(objects[7],56);
  display_begin_window_axis_move(1,0,-15*65536,0,15);
  display_enable_background(2);audio_play_animation_cue(12);
 } else if(timer==15) {
  int i;
  unsigned int base,value,first_offset;
  const unsigned char *entries;
  const unsigned short *colors;
  display_set_window_rectangle(1,0,160*65536,240*65536,160*65536);
  display_configure_window(1,63,60);
  display_set_background_scroll_target(1,0,0,15);
  display_set_background_scroll_target(0,0,0,15);
  display_begin_window_axis_move(1,0,0,0,timer);
  display_fill_background(0,0);
  g_scene_request.scene=8;
  for(i=8;i<=14;++i)scene_palette_menu_refresh_selector(i);
  display_enable_background(1);display_enable_background(0);
  { struct FrameObject **objects=g_frame_actor_palette_menu_objects;
  objects[8]->id=29;
  ((struct FrameActorObject*)objects[8])->need_timer=15;
  if(g_scene_palette_menu_owner->initial_word==0) {
   objects[8]->flags|=1;frame_set_variant_state(objects[8],56);
  } else {
   objects[8]->flags&=~1U;frame_set_variant_state(objects[8],58);
  }
  }
  { struct FrameObject **objects=g_frame_actor_palette_menu_objects;
  ((struct FrameActorObject*)objects[1])->need_timer=15;
  frame_set_variant_state(objects[1],56);
  objects[6]->id=(base=11);
  ((struct FrameActorObject*)objects[6])->need_timer=15;
  frame_set_variant_state(objects[6],56);
  objects[3]->unknown_0a=7;
  objects[4]->flags|=1;objects[6]->flags|=1;
  objects[3]->id=16;
  ((struct FrameActorObject*)objects[3])->need_timer=15;
  frame_set_variant_state(objects[3],56);
  objects[4]->id=23;
  ((struct FrameActorObject*)objects[4])->need_timer=15;
  frame_set_variant_state(objects[4],56);
  ((struct FrameActorObject*)objects[5])->need_timer=15;
  frame_set_variant_state(objects[5],58);
  objects[5]->flags&=~1U;
  entries=g_scene_palette_menu_owner->parameters;
  value=(entries+=g_scene_request.scene,entries[-6]);
  first_offset=(base-value)*2;
  colors=g_palette_menu_selector_colors;
  display_load_palette_alternate((const unsigned char*)colors+first_offset,65,1);
  ++value;display_load_palette_alternate(colors+value,81,1);
  }
 } else if(timer==1)display_disable_window(1);
 else if(timer==0) {
  g_scene_request.unknown_10=4;
  scene_palette_menu_build_selection_objects();
  if(g_scene_palette_menu_owner->initial_word==0)g_frame_actor_palette_menu_objects[8]->flags|=1;
  else g_frame_actor_palette_menu_objects[8]->flags&=~1U;
 }
 --g_scene_request.unknown_14;
}
asm(".align 2,0");
