#include "scene_palette_menu_selection_transition.h"
void scene_palette_menu_phase_10(void) {
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==30) {
  struct FrameObject **objects;
  scene_palette_menu_release_selection_objects();
  display_set_window_rectangle(1,0,0,240*65536,160*65536);
  display_configure_window(1,63,60);
  display_set_background_scroll_target(1,0,-160*65536,15);
  display_set_background_scroll_target(0,0,-160*65536,15);
  display_begin_window_axis_move(1,0,0,160*65536,15);
  objects=g_frame_actor_palette_menu_objects;
  ((struct FrameActorObject*)objects[1])->need_timer=16;
  frame_set_variant_state(objects[1],57);
  ((struct FrameActorObject*)objects[6])->need_timer=16;
  frame_set_variant_state(objects[6],57);
  ((struct FrameActorObject*)objects[3])->need_timer=16;
  frame_set_variant_state(objects[3],57);
  ((struct FrameActorObject*)objects[4])->need_timer=16;
  frame_set_variant_state(objects[4],57);
  ((struct FrameActorObject*)objects[5])->need_timer=16;
  frame_set_variant_state(objects[5],57);
  ((struct FrameActorObject*)objects[8])->need_timer=16;
  frame_set_variant_state(objects[8],57);
 } else if(timer==15) {
  struct FrameObject **objects;
  display_hide_background(0);display_hide_background(1);
  display_set_window_rectangle(1,-15*65536,0,240*65536,160*65536);
  display_configure_window(1,60,56);
  objects=g_frame_actor_palette_menu_objects;
  ((struct FrameActorObject*)objects[7])->need_timer=16;
  frame_set_variant_state(objects[7],57);
  display_set_background_scroll_target(2,0,100*65536,15);
  display_begin_window_axis_move(1,0,241*65536,0,timer);
 } else if(timer==1) {
  display_hide_background(2);display_disable_window(1);
 } else if(timer==0) {
  switch(g_scene_request.parameter) {
  case 14:resource_submit_scene(1,4,6);break;
  case 13:scene_submit_default_request(5);break;
  case 6:
   g_scene_request.unknown_10=6;g_scene_request.unknown_14=31;
   display_load_background(2,&g_frame_actor_palette_menu_background2,18,2,timer,timer);
   display_load_background(1,&g_frame_actor_palette_menu_background1,53,3,timer,timer);
   display_load_palette(g_frame_actor_palette_menu_entry_palette,64,16);
   { register unsigned int layer asm("r0")=2; register int x asm("r1")=0; int y=176*65536; display_set_background_scroll_target(layer,x,y,1); }
   { register unsigned int layer asm("r0")=1; register int x asm("r1")=256*65536; int y=0; display_set_background_scroll_target(layer,x,y,1); }
   { register unsigned int layer asm("r0")=0; int x=256*65536; int y=0; display_set_background_scroll_target(layer,x,y,1); }
   g_frame_actor_palette_menu_objects[0]->flags|=1;
   break;
  case 5:
   g_scene_request.unknown_10=11;g_scene_request.unknown_14=16;
   scene_palette_menu_prepare_selected_exit();break;
  }
 }
 --g_scene_request.unknown_14;
}
asm(".align 2,0");
