#include "frame_map.h"
void frame_install_map_routines(void) {
 resource_bios_swi_0b(g_frame_map_draw_rom,g_frame_map_draw_ram,0x04000054);
 resource_bios_swi_0b(g_frame_map_scroll_rom,g_frame_map_scroll_ram,0x04000039);
 g_frame_map_draw_routine=(void*)g_frame_map_draw_ram;
 g_frame_map_scroll_routine=(void*)g_frame_map_scroll_ram;
}
asm(".align 2,0");
