#include "scene_palette_menu_selection_transition.h"
void scene_palette_menu_phase_6(void) {
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==30) {
  struct FrameObject **objects;
  display_configure_window(1,63,59);
  display_set_window_rectangle(1,0,0,240*65536,0);
  display_set_background_scroll_target(2,0,0,15);
  display_begin_window_axis_move(1,1,240*65536,176*65536,15);
  display_enable_background(2);
  objects=g_frame_actor_palette_menu_objects;
  objects[2]->id=0;
  objects[2]->unknown_0a=4;
  audio_play_animation_cue(12);
 } else if(timer==15) {
  unsigned char i;
  struct FrameObject **objects;
  display_set_background_scroll_target(1,0,0,15);
  display_set_background_scroll_target(0,0,0,15);
  display_configure_window(1,28,63);
  display_set_window_rectangle(1,0,0,256*65536,256*65536);
  display_begin_window_axis_move(1,0,256*65536,0,timer);
  g_scene_request.scene=0;
  display_text_set_background_control(g_scene_palette_menu_control0);
  display_load_palette_alternate(g_scene_palette_menu_palette,0,16);
  display_fill_background(0,0);
  for(i=0;i<=7;++i)frame_draw_palette_menu_row(i);
  display_enable_background(1);
  display_enable_background(0);
  objects=g_frame_actor_palette_menu_objects;
  ((struct FrameActorObject *)objects[2])->need_timer=15;
  frame_set_variant_state(objects[2],56);
  objects[7]->id=9;
  ((struct FrameActorObject *)objects[7])->need_timer=15;
  frame_set_variant_state(objects[7],56);
  objects[8]->id=8;
  ((struct FrameActorObject *)objects[8])->need_timer=15;
  frame_set_variant_state(objects[8],56);
 } else if(timer==1)display_disable_window(1);
 else if(timer==0)g_scene_request.unknown_10=3;
 --g_scene_request.unknown_14;
}
asm(".align 2,0");
