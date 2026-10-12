#include "frame_actor_needs.h"
#include "frame_actor_state.h"
#include "audio_game.h"
void frame_actor_state_45(struct FrameObject *object)
{
 struct FrameObject *actor=g_frame_actor_need_input.views[0].actor;
 switch (((struct FrameActorObject*)object)->variant_state) {
 case 4:
  frame_set_actor_direction(object,frame_direction_toward(object,actor));
  frame_stop_motion(object);
  frame_set_actor_direction(actor,frame_direction_toward(actor,object));
  frame_stop_motion(actor);
  frame_stop_motion(object);
  frame_stop_motion(actor);
  transition_object_set_state(actor,0);
  frame_request_animation((struct FrameCommandObject*)object,40);
  frame_set_variant_state(object,44);
  break;
 case 44:
  if(object->flags&0x400000) {
   frame_request_animation((struct FrameCommandObject*)object,1);
   frame_set_variant_state(object,11);
   frame_request_animation((struct FrameCommandObject*)actor,43);
   audio_play_animation_cue(228);
  }
  break;
 case 11:
  if(actor->flags&0x400000) {
   frame_clear_animation_pending(actor);
   frame_set_actor_direction(object,4);
   frame_request_animation((struct FrameCommandObject*)object,1);
   frame_set_variant_state(object,43);
   ((struct FrameActorStateWork*)object)->timer=90;
   audio_play_animation_cue(229);
  }
  break;
 case 43:
  if(--((struct FrameActorStateWork*)object)->timer==-1)
   transition_object_set_state(actor,37);
  break;
 }
}
asm(".align 2, 0");
