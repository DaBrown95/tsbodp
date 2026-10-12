#include "display.h"
unsigned int display_find_palette_block(void)
{
    unsigned char index;
    for (index = 0; index < 12; ++index) {
        if (!(g_palette_block_jobs[index].flags & 1)) {
            ++g_palette_block_count;
            break;
        }
    }
    return index;
}
