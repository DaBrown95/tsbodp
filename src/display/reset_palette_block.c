#include "display.h"
void display_reset_palette_block(struct PaletteBlockJob *job)
{
    display_set_bytes(job, 0, 20);
    if (g_palette_block_count) --g_palette_block_count;
}
