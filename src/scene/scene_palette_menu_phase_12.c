#include "scene_palette_menu_text_transition.h"
void scene_palette_menu_phase_12(void) {
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==15) {
  struct FrameObject **objects;
  display_set_window_rectangle(1,0,0,240*65536,160*65536);
  display_configure_window(1,63,60);
  display_set_background_scroll_target(1,0,-160*65536,15);
  display_set_background_scroll_target(0,0,-160*65536,15);
  display_begin_window_axis_move(1,0,0,160*65536,timer);
  objects=g_frame_actor_palette_menu_objects;
  ((struct FrameActorObject*)objects[8])->need_timer=16;
  frame_set_variant_state(objects[8],57);
  ((struct FrameActorObject*)objects[9])->need_timer=16;
  frame_set_variant_state(objects[9],57);
 } else if(timer==1) {
  display_hide_background(1);display_hide_background(0);display_disable_window(1);
 } else if(timer==0) {
  switch(g_scene_request.parameter) {
   case 14:scene_submit_default_request(25);break;
   case 13:scene_submit_default_request(5);break;
   case 9:
    g_scene_request.unknown_10=9;
    g_scene_request.unknown_14=31;
    display_fill_background(2,18);
    display_load_background(2,&g_palette_menu_mode7_background2,18,2,timer,timer);
    { register unsigned int layer asm("r0")=2; register int x asm("r1")=0; int y=-100*65536; display_set_background_position(layer,x,y); }
    display_load_background(1,&g_palette_menu_mode7_background1,44,3,timer,timer);
    display_load_palette(g_frame_actor_palette_menu_entry_palette,64,16);
    { register unsigned int layer asm("r0")=2; register int x asm("r1")=0; int y=100*65536; display_set_background_scroll_target(layer,x,y,1); }
    { register unsigned int layer asm("r0")=1; register int x asm("r1")=0; register int y asm("r2")=-160*65536; display_set_background_scroll_target(layer,x,y,1); }
    { register unsigned int layer asm("r0")=0; register int x asm("r1")=0; int y=-160*65536; display_set_background_scroll_target(layer,x,y,1); }
    break;
  }
 }
 --g_scene_request.unknown_14;
}
asm(".align 2,0");
