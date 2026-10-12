#include "display.h"
void display_commit_palette_range(struct PaletteRangeJob *job)
{
    struct PaletteBufferPair *buffers;
    unsigned int selection, count, offset;
    unsigned short *source, *destination;
    if (job->flags & 2) {
        job->flags &= ~2;
        selection = job->flags & 4;
        buffers = g_palette_buffer_pairs;
        if (selection)
            ++buffers;
        if (job->destination_first == job->source_first) {
            DISPLAY_DMA3->source = (unsigned int)(buffers->staging + job->source_first);
            DISPLAY_DMA3->destination = (unsigned int)(buffers->destination + job->source_first);
            DISPLAY_DMA3->control = job->count | 0x80000000;
            DISPLAY_DMA3->control;
        } else {
            count = job->destination_last - job->destination_first + 1;
            DISPLAY_DMA3->source = (offset = job->source_first * 2, (unsigned int)(source = buffers->staging) + offset);
            DISPLAY_DMA3->destination = (offset = job->destination_first * 2, (unsigned int)(destination = buffers->destination) + offset);
            DISPLAY_DMA3->control = count | 0x80000000;
            DISPLAY_DMA3->control;
            count = job->destination_first - job->source_first;
            source = (unsigned short *)((unsigned int)source + (job->destination_last - count + 1) * 2);
            DISPLAY_DMA3->source = (unsigned int)source;
            destination += job->source_first;
            DISPLAY_DMA3->destination = (unsigned int)destination;
            DISPLAY_DMA3->control = count | 0x80000000;
            DISPLAY_DMA3->control;
        }
    }
}
