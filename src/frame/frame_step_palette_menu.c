#include "frame_actor_palette_menu.h"
#include "scene_request.h"
#include "input.h"
void frame_step_palette_menu(void)
{
 unsigned int pressed=g_input_pressed[g_input_config.local_player];
 unsigned int confirmed=pressed&1;
 if(confirmed) {
  struct SceneRequest *state=&g_scene_request;
  state->unknown_10=8;
  state->unknown_14=30;
  state->parameter=9;
  audio_play_animation_cue(12);
 } else if(pressed&2) {
  struct SceneRequest *state=&g_scene_request;
  state->unknown_10=8;
  state->unknown_14=30;
  state->parameter=0;
  audio_play_animation_cue(12);
 } else {
  unsigned int direction=240;
  direction &= pressed;
  if(direction) {
  struct SceneRequest *state=&g_scene_request;
  unsigned int previous=state->scene;
  frame_step_palette_menu_choices();
  if(previous!=state->scene) {
   struct FrameObject **objects;
   frame_draw_palette_menu_row(previous);
   frame_draw_palette_menu_row(state->scene);
   objects=g_frame_actor_palette_menu_objects;
   objects[2]->id=state->scene;
   frame_set_variant_state(objects[2],58);
   if(state->scene==7) {
    objects[2]->unknown_0a=5;
    display_scene_refresh_item(objects[2]);
   } else {
    objects[2]->unknown_0a=4;
    display_scene_refresh_item(objects[2]);
   }
  }
 }
 }
}
asm(".align 2, 0");
