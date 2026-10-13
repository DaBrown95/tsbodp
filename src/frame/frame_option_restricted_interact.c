#include "frame_option_object.h"

void frame_option_restricted_interact(struct FrameObject *base,struct FrameObject *other)
{
 struct FrameOptionObject *actor=(struct FrameOptionObject *)other;
 frame_need_effect_stop_at_position(base);
 frame_need_effect_stop_at_position(other);
 if(actor->id==0 && actor->state==16 && frame_scene_effect_facing_available(base,other)) {
  frame_disable_object_flags(base,4);
  frame_set_variant_state(base,5);
  frame_request_animation((struct FrameCommandObject *)other,69);
  frame_set_variant_state(other,47);
  transition_object_set_state((struct TransitionObject *)other,47);
  audio_play_animation_cue(184);
  audio_play_animation_cue(46);
 }
}
asm(".align 2, 0");
