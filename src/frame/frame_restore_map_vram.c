#include "frame_map.h"
void frame_restore_map_vram(void) {
 resource_bios_swi_0c(g_frame_map_store.default_resource,(void*)0x06000000,0x3000);
 heap_free(g_frame_map_store.default_resource);
 g_frame_map_store.default_resource=0;
}
asm(".align 2,0");
