#include "frame_render_effect.h"
void frame_clear_render_effects(void){
 if(g_frame_render_effect_count){
  struct FrameRenderEffect *effect=g_frame_render_effect_head;
  while(effect){
   struct FrameRenderEffect *next=effect->next;
   frame_destroy_render_effect(effect);
   effect=next;
  }
 }
}
