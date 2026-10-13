#include "frame_need_effect_optional_state.h"

unsigned char frame_need_effect_try_actor_effect(struct FrameNeedEffectState *state,struct FrameObject *actor)
{
 unsigned char ready;
 if(g_need_effect_player==actor)
  ready=frame_random_chance(frame_read_signed_parameter(g_frame_actor_social_probe,1)+15);
 else ready=0;
 if(ready==1) {
  if(((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90) {
   transition_object_set_state(((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90,1);
   ((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90=0;
  }
  ((struct FrameNeedOptionalObjectView *)state->object)->object_slot_90=frame_create_actor_effect(state->object,200,8,1);
  if(g_frame_interaction_settings.attachment_mode==1)audio_play_animation_cue(153);
  else audio_play_animation_cue(154);
  ((struct FrameActorObject *)actor)->default_state=40;
 }
 return ready;
}
asm(".align 2, 0");
