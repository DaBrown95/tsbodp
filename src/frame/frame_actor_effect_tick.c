#include "frame_actor_runtime.h"
#include "audio_game.h"
#include "frame_actor_effect.h"
void frame_actor_effect_tick(struct FrameObject *base)
{
 struct FrameActorEffectObject *object=(struct FrameActorEffectObject *)base;
 unsigned int flags,mask;
 switch(object->state) {
 case 0:
  if(object->completion_mode==1){flags=object->flags;mask=0x400000;}
  else{flags=object->owner->flags;mask=2;}
  if(flags&mask)transition_object_set_state(base,1);
  break;
 case 1:
  object->flags|=2;
  audio_game_stop_sample(object->cue_handle);
  break;
 case 5:
  if(object->flags&0x400000)transition_object_set_state(base,1);
  break;
 }
}
