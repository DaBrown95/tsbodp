#include "frame_map.h"
void frame_get_alternate_map_dimensions(struct FramePoint *point) {
 point->x=g_frame_map_store.views[1].width << 5;
 point->y=g_frame_map_store.views[1].height << 5;
}
asm(".align 2, 0");
