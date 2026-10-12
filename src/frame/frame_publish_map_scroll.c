#include "frame_map.h"
#include "input.h"
#include "background_animation.h"
void frame_publish_map_scroll(void) {
 if(g_irq_context->transfer_ready==1) {
  volatile unsigned short *registers;
  g_frame_map_scroll_routine(g_input_config.local_player);
  *(volatile unsigned short *)0x04000014=g_frame_map_store.views[1].fractional_scroll.x;
  *(volatile unsigned short *)0x04000016=g_frame_map_store.views[1].fractional_scroll.y;
  *(volatile unsigned short *)0x04000018=g_frame_map_store.views[0].fractional_scroll.x;
  *(volatile unsigned short *)0x0400001A=g_frame_map_store.views[0].fractional_scroll.y;
  if(g_background_animation.flags&1) {
   if(g_background_animation.transfer_enabled>1) {
    registers=(volatile unsigned short *)0x0400001C;
    *registers++=g_frame_map_store.views[0].origins[g_input_config.local_player].x;
    *registers=g_frame_map_store.views[0].origins[g_input_config.local_player].y;
   } else {registers=(volatile unsigned short *)0x0400001C;*registers=g_frame_map_store.views[0].origins[g_input_config.local_player].x;}
  }
 }
}
