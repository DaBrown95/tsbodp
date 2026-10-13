#include "frame_grid_selection.h"
void frame_grid_selection_interact(struct FrameObject *base)
{
 struct FrameActorObject *object=(struct FrameActorObject *)base;
 if(g_grid_selected_need_effect_object && object->state==16 && object->variant_state!=52 && object->variant_state!=53 && g_save_world_transition_rows[object->unknown_13].ticks==0 && g_need_effect_game_state[0x42e]==0) {
  unsigned short pressed=g_input_pressed[object->unknown_13];
  if(pressed&1) {
   if(frame_need_effect_begin_choices(g_grid_selected_need_effect_object,base)==1) {
    input_clear();
    frame_need_effect_stop_at_position(base);
   }
  } else {
   unsigned int triggered=0x100;
   triggered &= pressed;
   if(triggered) {
   if(frame_world_in_idle_exclusion_set(g_frame_world_id)==1) {
    if(frame_need_effect_cycle_mode(g_grid_selected_need_effect_object)==1)audio_play_animation_cue(16);
    else audio_play_animation_cue(3);
   } else audio_play_animation_cue(3);
   }
  }
 }
}
