#include "scene_palette_menu_text_transition.h"
void scene_palette_menu_phase_11(void) {
 unsigned int timer=g_scene_request.unknown_14;
 if(timer==30) {
 } else if(timer==15) {
  unsigned int tile;
  struct FrameObject **objects;
  display_set_window_rectangle(1,0,160*65536,240*65536,160*65536);
  display_configure_window(1,63,60);
  display_set_background_scroll_target(1,0,0,15);
  display_set_background_scroll_target(0,0,0,15);
  display_begin_window_axis_move(1,0,0,0,timer);
  display_fill_background(0,0);
  g_scene_request.scene=0;
  display_text_select_font(3,0,0);
  { register unsigned int line_style asm("r5")=1;
  tile=display_text_draw_all_lines(1,120,48,185,display_scene_lookup_text(33),line_style); }
  tile=display_text_draw_line(tile,85,88,display_scene_lookup_text(34),0);
  display_text_draw_line(tile,150,88,display_scene_lookup_text(35),0);
  display_enable_background(1);
  display_enable_background(0);
  objects=g_frame_actor_palette_menu_objects;
  objects[8]->id=30;
  ((struct FrameActorObject*)objects[8])->need_timer=timer;
  frame_set_variant_state(objects[8],56);
  objects[9]->id=31;
  ((struct FrameActorObject*)objects[9])->need_timer=timer;
  frame_set_variant_state(objects[9],56);
  audio_play_animation_cue(12);
 } else if(timer==1)display_disable_window(1);
 else if(timer==0)g_scene_request.unknown_10=5;
 --g_scene_request.unknown_14;
}
asm(".align 2,0");
