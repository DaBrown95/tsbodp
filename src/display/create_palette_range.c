#include "display.h"
#include "display_palette_lifecycle.h"

unsigned int display_create_palette_range(unsigned int first, unsigned int count,
    unsigned int interval, unsigned int flags)
{
    unsigned int index = display_next_palette_range();
    struct PaletteRangeJob *job = &g_palette_range_jobs[index];
    job->flags = flags;
    job->interval = interval;
    job->delay = 0;
    job->source_first = first;
    job->destination_first = first;
    first += count;
    --first;
    job->destination_last = first;
    job->count = count;
    job->original_count = count;
    return index;
}
