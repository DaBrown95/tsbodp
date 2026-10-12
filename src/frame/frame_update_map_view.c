#include "frame_map.h"
#include "input.h"
#include "background_animation.h"
void frame_update_map_view(unsigned char view) {
 struct FramePoint point,dimensions;
 transition_get_view_position(&point,view);
 point.x-=0x780000;
 point.y-=0x500000;
 point.y-=((int)g_frame_view_vertical_adjust<<16);
 point.x>>=16;point.y>>=16;
 frame_get_map_dimensions(&dimensions);
 if(point.x<0)point.x=0;
 else if(point.x>dimensions.x-240)point.x=dimensions.x-240;
 if(point.y<0)point.y=0;
 else if(point.y>dimensions.y-160)point.y=dimensions.y-160;
 g_frame_view_origins[view]=point;
 if(view!=g_input_config.local_player || !(g_frame_flags&0x110000)) {
  g_frame_map_store.views[0].origins[view]=point;
  g_frame_map_store.views[1].origins[view]=point;
  if(g_input_config.local_player==view) {
   g_frame_map_store.views[0].fractional_scroll.x=point.x&7;
   g_frame_map_store.views[0].fractional_scroll.y=point.y&7;
   g_frame_map_store.views[1].fractional_scroll.x=point.x&7;
   g_frame_map_store.views[1].fractional_scroll.y=point.y&7;
   g_frame_map_draw_routine(view);
  }
 } else {
  g_frame_map_store.views[0].origins[view].x=0;
  g_frame_map_store.views[0].origins[view].y=0;
  g_frame_map_store.views[1].origins[view].x=0;
  g_frame_map_store.views[1].origins[view].y=0;
  g_frame_map_store.views[0].fractional_scroll.x=0;
  g_frame_map_store.views[0].fractional_scroll.y=0;
  g_frame_map_store.views[1].fractional_scroll.x=0;
  g_frame_map_store.views[1].fractional_scroll.y=0;
 }
}
