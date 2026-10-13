#include "frame_render_effect.h"
int frame_step_render_effect(struct FrameRenderEffect *effect)
{
 int result=0;
 unsigned char terrain;
 if(--effect->countdown == -1){
  frame_destroy_render_effect(effect);
  goto done;
 }
 switch(effect->motion_mode){
  case 0: frame_step_render_effect_animation(effect); break;
  case 1: frame_step_render_effect_linear(effect); break;
  case 2: frame_step_render_effect_linear_alternate(effect);break;
  default: frame_step_render_effect_linear_alternate(effect);break;
 }
 if(effect->flags&8){
  unsigned int index=g_frame_render_direction_indices[effect->direction];
  const int *components=g_frame_velocity_default;
  unsigned int byte_offset=index*8; const int *y_components=components+1; int component=*(const int *)(byte_offset+(unsigned int)y_components);
  effect->position.fixed.x=effect->origin.x+effect->amplitude*frame_fixed_multiply(component,frame_sine(effect->phase));
  { int x_component=*(const int *)((unsigned int)components+byte_offset);
  effect->position.fixed.y=effect->origin.y+effect->amplitude*frame_fixed_multiply(x_component,frame_sine(effect->phase)); }
  effect->phase+=effect->phase_step;
 }else if(effect->flags&0x20){
  effect->position.fixed.x=effect->origin.x+effect->amplitude*frame_cosine(effect->phase);
  effect->position.fixed.y=effect->origin.y+effect->amplitude*frame_sine(effect->phase);
  effect->phase+=effect->phase_step;
 }else{
  effect->position.fixed.x=effect->origin.x;
  effect->position.fixed.y=effect->origin.y;
 }
 if(!(effect->flags&0x80))terrain=frame_render_effect_terrain(effect);
 else terrain=0;
 if(!(g_frame_flags&0x110000)){
  if(terrain==3)frame_destroy_render_effect(effect);
  else {
   result=(signed char)frame_draw_render_effect(effect);
   if(result==-1){g_frame_render_effect_pending=1;return result;}
  }
 }
 done: return (signed char)result;
}
