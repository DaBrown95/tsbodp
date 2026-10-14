#include "scene_palette_menu_selection_transition.h"
void scene_palette_menu_phase_8(void) {
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==30) {
  struct FrameObject **objects;
  display_set_background_scroll_target(0,256*65536,0,15);
  display_set_background_scroll_target(1,256*65536,0,15);
  display_configure_window(1,28,63);
  display_set_window_rectangle(1,256*65536,0,256*65536,160*65536);
  display_begin_window_axis_move(1,0,0,0,15);
  objects=g_frame_actor_palette_menu_objects;
  ((struct FrameActorObject *)objects[2])->need_timer=16;
  frame_set_variant_state(objects[2],57);
  ((struct FrameActorObject *)objects[7])->need_timer=16;
  frame_set_variant_state(objects[7],57);
  ((struct FrameActorObject *)objects[8])->need_timer=16;
  frame_set_variant_state(objects[8],57);
 } else if(timer==15) {
  display_hide_background(1);display_hide_background(0);
  display_set_background_scroll_target(2,0,176*65536,15);
  display_set_window_rectangle(1,0,176*65536,240*65536,176*65536);
  display_configure_window(1,56,60);
  display_begin_window_axis_move(1,0,0,0,timer);
 } else if(timer==0) {
  display_hide_background(2);display_disable_window(1);
  switch(g_scene_request.parameter) {
  case 14:resource_submit_scene(1,4,6);break;
  case 13:scene_submit_default_request(5);break;
  case 0:
   g_scene_request.unknown_10=0;g_scene_request.mode=7;g_scene_request.unknown_14=32;
   g_frame_actor_palette_menu_objects[0]->flags&=~1U;
   break;
  case 9:
   g_scene_request.unknown_10=9;g_scene_request.unknown_14=31;
   scene_palette_menu_finish_mode_seven();
   g_frame_actor_palette_menu_objects[0]->flags&=~1U;
   break;
  }
 }
 --g_scene_request.unknown_14;
}
asm(".align 2,0");
