#include "frame_actor_needs.h"
#include "audio_game.h"
void frame_handle_actor_empty_needs(struct FrameActorNeedState *state, struct FrameActorObject *object)
{
 unsigned int mask = frame_empty_need_mask(state);
 if (mask && !(mask & 0x20) && (mask & 5) && object->variant_state != 69 && object->variant_state != 6) {
  transition_object_set_state((struct FrameObject *)object, 47);
  frame_set_variant_state((struct FrameObject *)object, 69);
  frame_request_animation((struct FrameCommandObject *)object, 72);
  audio_play_animation_cue(30);
  if (!g_frame_actor_cue_options.variant) audio_play_animation_cue(152); else audio_play_animation_cue(151);
 }
}
