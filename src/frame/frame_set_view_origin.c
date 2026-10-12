#include "frame_map.h"
void frame_set_view_origin(struct FramePoint *point, unsigned char index) {
 g_frame_view_origins[index].x=point->x;
 g_frame_view_origins[index].y=point->y;
}
asm(".align 2, 0");
