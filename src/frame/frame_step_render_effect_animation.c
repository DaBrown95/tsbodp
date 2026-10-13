#include "frame_render_effect.h"
void frame_step_render_effect_animation(struct FrameRenderEffect *effect)
{
 if(++effect->animation_ticks>=effect->animation_delay || effect->frame==-1){
  if(effect->frame<effect->resource->sequence->frame_count-1)effect->frame++;
  else if(effect->flags&4)effect->frame=0;
  effect->animation_ticks=0;
 }
}
