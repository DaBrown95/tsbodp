#include "frame_map.h"
void frame_get_map_dimensions(struct FramePoint *point) {
 if (display_get_mode() <= 2) {
  point->x=g_frame_map_store.views[0].width << 5;
  point->y=g_frame_map_store.views[0].height << 5;
 } else {
  point->x=240;
  point->y=160;
 }
}
asm(".align 2, 0");
