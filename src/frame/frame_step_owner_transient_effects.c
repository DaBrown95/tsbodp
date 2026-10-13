#include "frame_render_effect.h"
#include "frame_transient_effect.h"
void frame_step_owner_transient_effects(struct FrameObject *owner){
 if(g_frame_transient_count){
  struct FrameTransientEffect *effect=(struct FrameTransientEffect *)g_frame_transient_active_list.first;
  while(effect){
   struct FrameTransientEffect *next=effect->next;
   if(effect->owner==owner){
    frame_step_transient_effect(effect);
    effect->flags|=0x8000;
   }
   effect=next;
  }
  g_frame_render_effect_pending=0;
 }
}
