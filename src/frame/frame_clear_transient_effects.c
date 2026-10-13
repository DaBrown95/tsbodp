#include "frame_render_effect.h"
#include "frame_transient_effect.h"
void frame_clear_transient_effects(void){
 if(g_frame_transient_count){
  struct FrameTransientEffect *effect=(struct FrameTransientEffect *)g_frame_transient_active_list.first;
  while(effect){
   struct FrameTransientEffect *next=effect->next;
   frame_pool_release(g_frame_transient_free_pool,&g_frame_transient_active_list,(struct FrameObject *)effect);
   g_frame_transient_count--;
   effect=next;
  }
 }
}
