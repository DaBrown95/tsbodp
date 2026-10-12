#include "frame_map.h"
void frame_get_view_origin(struct FramePoint *point, unsigned char index) {
 point->x=g_frame_view_origins[index].x;
 point->y=g_frame_view_origins[index].y;
}
asm(".align 2, 0");
