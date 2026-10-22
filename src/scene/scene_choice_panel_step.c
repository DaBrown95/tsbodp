#include "scene_choice_panel_step.h"
void scene_choice_panel_step(void)
{
 struct FrameObject *actor=SCENE_CHOICE_PANEL_INPUT_ACTOR(SCENE_CHOICE_PANEL_LOCAL_PLAYER);
 switch(g_scene_request.unknown_10) {
 case 0: {
  unsigned int x,y;
  int left,top,right,bottom;
  display_configure_window_masks(63,62,63);
  x=SCENE_CHOICE_PANEL_X;
  left=x<<19;
  y=SCENE_CHOICE_PANEL_Y;
  top=y<<19;
  right=(g_scene_choice_panel_size.width+x)<<19;
  bottom=(g_scene_choice_panel_size.height+y)<<19;
  scene_choice_panel_original_set_window(left,top,right,bottom);
  g_scene_request.unknown_10=1;
  break;
 }
 case 1:
  scene_view_draw_frame(SCENE_CHOICE_PANEL_X,SCENE_CHOICE_PANEL_Y,g_scene_choice_panel_size.width,g_scene_choice_panel_size.height);
  audio_play_animation_cue(4);
  scene_choice_panel_draw_text();
  scene_choice_panel_original_window_begin(10);
  g_scene_request.unknown_10=2;
  g_scene_request.unknown_14=10;
  break;
 case 2:
  if(--g_scene_request.unknown_14==~0U) {
   if(g_actor_scene_request.active==1 && g_actor_scene_request.object) g_actor_scene_request.object->flags|=1;
   g_scene_request.unknown_10=4;
  }
  break;
 case 3:
  if(--g_scene_request.unknown_14==~0U) {
   display_fill_background_constant_rectangle(0,SCENE_CHOICE_PANEL_X,SCENE_CHOICE_PANEL_Y,
    g_scene_choice_panel_size.width,g_scene_choice_panel_size.height,0);
   scene_submit_default_request(g_resource_scene_arg);
  }
  break;
 case 4: {
  unsigned int player;
  const InputU16 *pressed_table;
  if(SCENE_CHOICE_PANEL_ACTOR_VARIANT(actor)!=5 && (SCENE_CHOICE_PANEL_ACTOR_STATE(actor)==16 || SCENE_CHOICE_PANEL_ACTOR_STATE(actor)==27)) {
   if(g_input_pressed[SCENE_CHOICE_PANEL_LOCAL_PLAYER]&8) {
    SCENE_CHOICE_PANEL_REQUESTED_KIND=14;
    scene_submit_default_request(14);
    audio_play_animation_cue(4);
   } else if((g_input_pressed[0]&4) || (g_input_pressed[1]&4)) {
    scene_submit_default_request(11);
    audio_play_animation_cue(4);
   }
  }
  pressed_table=g_input_pressed;
  player=SCENE_CHOICE_PANEL_LOCAL_PLAYER;
  if(pressed_table[player]&1) {
   scene_choice_panel_begin_close();
   if(g_actor_scene_request.active==1) g_scene_request.parameter=~0U;
   else g_scene_request.parameter=g_scene_request.scene;
  } else if(pressed_table[player]&2) {
   scene_choice_panel_begin_close();
   g_scene_request.parameter=~0U;
  } else if(pressed_table[player]&0xf0) {
   if(!g_actor_scene_request.active) {
    if((SCENE_CHOICE_PANEL_FLAGS&1) && SCENE_CHOICE_PANEL_COUNT>1)
     input_step_vertical_pressed(&g_scene_request.scene,1,SCENE_CHOICE_PANEL_COUNT-1,1,player);
    else input_step_vertical_pressed(&g_scene_request.scene,0,SCENE_CHOICE_PANEL_COUNT-1,1,SCENE_CHOICE_PANEL_LOCAL_PLAYER);
   }
   scene_choice_panel_draw_text();
  }
  break;
 }
 }
}
asm(".align 2,0");
