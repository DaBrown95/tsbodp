#include "display.h"
#include "display_palette_lifecycle.h"

void display_reset_palette_blocks(void)
{
    unsigned int index;
    struct PaletteBlockJob *job;
    g_palette_block_count = 0;
    index = 0;
    job = g_palette_block_jobs;
    do {
        display_reset_palette_block(job);
        ++job;
        ++index;
    } while (index <= 11);
}
