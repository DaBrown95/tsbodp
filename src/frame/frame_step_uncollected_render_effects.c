#include "frame_render_effect.h"
int frame_step_uncollected_render_effects(void) {
 int result=0;
 struct FrameRenderEffect *effect=g_frame_render_effect_head;
 while(effect){
 struct FrameRenderEffect *next=effect->next;
 if(!(effect->flags&0x8000)){
  result=(signed char)frame_step_render_effect(effect);
  if(result==-1)return (signed char)result;
 }
 effect->flags&=~0x8000;
 effect=next;
 }
 return (signed char)result;
}
