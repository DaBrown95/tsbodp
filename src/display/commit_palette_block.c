#include "display.h"
void display_commit_palette_block(struct PaletteBlockJob *job)
{
    struct PaletteBufferPair *buffers;
    unsigned int selection;
    if (job->flags & 2) {
        job->flags &= ~2;
        selection = job->flags & 4;
        buffers = g_palette_buffer_pairs;
        if (selection)
            ++buffers;
        DISPLAY_DMA3->source = (unsigned int)buffers->staging + job->first * 2;
        DISPLAY_DMA3->destination = (unsigned int)buffers->destination + job->first * 2;
        DISPLAY_DMA3->control = job->count | 0x80000000;
        DISPLAY_DMA3->control;
    }
}
