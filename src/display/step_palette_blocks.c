#include "display.h"
void display_step_palette_blocks(void)
{
    unsigned char visited = 0;
    unsigned int index = 0;
    while (index <= 11 && visited <= g_palette_block_count) {
        struct PaletteBlockJob *job = &g_palette_block_jobs[index];
        if (job->flags & 1) {
            display_step_palette_block(job);
            ++visited;
        }
        ++index;
    }
}
