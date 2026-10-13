#include "frame_render_effect.h"
int frame_finish_layer(unsigned char layer){
 int result=0,index;
 if(!g_frame_render_effect_counts[layer])return 0;
 for(index=g_frame_render_effect_counts[layer]-1;index>=0;index--){
  unsigned int address=(unsigned int)g_frame_render_effect_lists[layer]; struct FrameRenderEffect *effect; address+=index*4; effect=*(struct FrameRenderEffect **)address;
  result=(signed char)frame_step_render_effect(effect);
  effect->flags&=~0x8000;
 }
 return result;
}
