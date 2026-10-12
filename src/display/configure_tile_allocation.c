#include "display.h"
void display_configure_tile_allocation(unsigned char mode)
{
    unsigned char *allocated;
    if ((unsigned char)(mode - 3) <= 2) {
        allocated = (unsigned char *)g_display_allocated_tiles;
        display_fill_bytes(allocated, 0xff, 0x40);
        display_fill_bytes(allocated + 0x40, 0, 0x40);
    } else {
        display_fill_bytes(g_display_allocated_tiles, 0, 0x80);
        display_fill_bytes(g_display_pending_free_tiles, 0xff, 0x80);
    }
}
