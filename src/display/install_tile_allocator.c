#include "display.h"
void display_install_tile_allocator(void)
{
    display_cpu_copy(g_display_tile_allocator_rom, g_display_tile_allocator_ram, 0x04000032);
}
