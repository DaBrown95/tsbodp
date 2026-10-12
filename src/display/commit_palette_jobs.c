#include "display.h"
void display_commit_palette_jobs(void)
{
    unsigned int i, j;
    struct PaletteRangeJob *range;
    struct PaletteBlockJob *block;
    for (i = 0; i < 12; ++i) {
        range = &g_palette_range_jobs[i];
        if (range->flags & 1)
            display_commit_palette_range(range);
    }
    for (j = 0; j < 12; ++j) {
        block = &g_palette_block_jobs[j];
        if (block->flags & 1)
            display_commit_palette_block(block);
    }
}
