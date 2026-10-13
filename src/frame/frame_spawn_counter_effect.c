#include "frame_actor_runtime.h"
#include "audio_game.h"
#include "frame_transient_effect.h"
void frame_spawn_counter_effect(struct FrameObject *owner,signed char delta)
{
 struct FrameTransientEffect *effect;
 if(delta<0) {effect=frame_create_transient_effect(6,0,6);audio_play_animation_cue(81);}
 else if(delta>0) {effect=frame_create_transient_effect(1,0,7);audio_play_animation_cue(82);}
 else effect=0;
 if(effect) {
  effect->owner=owner;
  effect->position.x=owner->position.x;
  effect->position.y=owner->position.y-(60<<16);
  effect->phase=3;
  effect->flags|=0x248a;
  effect->height=60;
  effect->enabled=1;
  effect->countdown=1;
  effect->unknown34=0;
  effect->direction=0;
  effect->rate=0x8000;
  effect->offset_x=5;
  effect->offset_y=20;
 }
}
