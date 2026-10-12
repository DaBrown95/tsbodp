#include "display.h"
unsigned int display_create_palette_block(unsigned int first, unsigned int count,
    unsigned int duration, unsigned int interval, unsigned int flags,
    const unsigned short *palette)
{
    unsigned int index = display_find_palette_block();
    struct PaletteBlockJob *job = &g_palette_block_jobs[index];
    job->flags = flags;
    job->duration = duration;
    job->remaining = duration;
    job->delay = interval;
    job->interval = interval;
    job->first = first;
    first += count;
    --first;
    job->last = first;
    job->count = count;
    job->palette_count = 0;
    job->palette_index = 0;
    job->palettes = palette;
    job->target = palette;
    return index;
}
