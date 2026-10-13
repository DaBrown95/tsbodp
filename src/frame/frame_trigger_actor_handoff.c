#include "frame_trigger_objects.h"

void frame_trigger_actor_handoff(struct FrameObject *base,unsigned int mode,struct FrameObject *source)
{
 struct FrameTriggerObject *actor=(struct FrameTriggerObject *)base;
 switch(mode) {
 case 0:
  if(actor->variant_state==65 || actor->variant_state==67 || actor->variant_state==68) break;
  { register union ResourceGameState *world asm("r0")=&g_resource_game_state;
   if(((unsigned char *)world)[0x42e]) break;
  }
  actor->position.x=source->position.x;
  actor->next_position.x=source->position.x;
  actor->position.y=source->position.y;
  actor->next_position.y=source->position.y;
  actor->velocity.x=0; actor->velocity.y=0;
  actor->flags&=~0x400000;
  transition_object_set_state((struct TransitionObject *)base,42);
  frame_request_animation((struct FrameCommandObject *)base,37);
  frame_set_variant_state(base,65);
  audio_play_animation_cue(28);
  actor->direction=7;
  break;
 case 1:
  if((unsigned char)(actor->variant_state-67)>1) break;
  actor->position.x=source->position.x;
  actor->next_position.x=source->position.x;
  actor->position.y=source->position.y;
  actor->next_position.y=source->position.y;
  actor->velocity.x=0; actor->velocity.y=0;
  actor->flags&=~0x400000;
  transition_object_set_state((struct TransitionObject *)base,42);
  frame_request_animation((struct FrameCommandObject *)base,38);
  frame_set_variant_state(base,66);
  audio_play_animation_cue(30);
  actor->direction=3;
  break;
 }
}
asm(".align 2, 0");
