#include "frame_map.h"
void frame_set_map_sources(const void *first, const void *second) {
    g_frame_map_store.views[0].source = first;
    g_frame_map_store.views[1].source = second;
}
asm(".align 2, 0");
