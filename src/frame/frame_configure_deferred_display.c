#include "frame_map_scene.h"
void frame_configure_deferred_display(unsigned char layer) {g_frame_queue.deferred_refresh=layer;}
asm(".align 2,0");
