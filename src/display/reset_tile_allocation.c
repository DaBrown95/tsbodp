#include "display.h"
void display_reset_tile_allocation(void)
{
    display_fill_bytes(g_display_allocated_tiles, 0, 0x80);
    display_fill_bytes(g_display_pending_free_tiles, 0xff, 0x80);
}
