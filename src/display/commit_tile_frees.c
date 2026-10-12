#include "display.h"
void display_commit_tile_frees(void)
{
    unsigned int i, clear;
    unsigned int *pending, *allocated;
    i = 0;
    clear = ~0;
    pending = g_display_pending_free_tiles;
    allocated = g_display_allocated_tiles;
    for (; i < 32; ++i) {
        *allocated++ &= *pending;
        *pending++ = clear;
    }
}
