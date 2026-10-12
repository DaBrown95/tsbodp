#include "frame_actor_runtime.h"
#include "frame_actor_state.h"
#include "audio_game.h"

void frame_actor_state_40(struct FrameObject *object)
{
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 0:
 case 2:
  ((struct FrameActorStateWork *)object)->cue_handle = audio_play_animation_cue(46);
  frame_request_animation((struct FrameCommandObject *)object, 68);
  frame_set_variant_state(object, 47);
  ((struct FrameActorStateWork *)object)->timer = 60;
  break;
 case 47:
  if (--((struct FrameActorStateWork *)object)->timer == -1) {
   audio_game_stop_sample(((struct FrameActorStateWork *)object)->cue_handle);
   frame_request_animation((struct FrameCommandObject *)object, 69);
   transition_object_set_state(object, 47);
  }
  break;
 }
}
asm(".align 2, 0");
