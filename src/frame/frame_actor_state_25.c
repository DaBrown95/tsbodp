#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "audio_game.h"

void frame_actor_state_25(struct FrameObject *object)
{
 switch (((struct FrameActorObject *)object)->variant_state) {
 case 0:
  if (object->flags & 0x400000) {
   frame_request_animation((struct FrameCommandObject *)object, 90);
   frame_set_variant_state(object, 22);
   audio_play_animation_cue(161);
  }
  break;
 case 22:
  if (object->flags & 0x400000) {
   transition_object_set_state(g_frame_actor_need_input.views[0].actor, 37);
   audio_play_animation_cue(27);
  } else if (((struct FrameActorObject *)object)->frame == 15) {
   audio_play_animation_cue(78);
  }
  break;
 }
}
asm(".align 2, 0");
