#include "display.h"
#include "display_palette_lifecycle.h"

void display_configure_palette_range(unsigned int index, unsigned int interval,
    unsigned int flags)
{
    struct PaletteRangeJob *job = &g_palette_range_jobs[index];
    job->flags = flags;
    job->interval = interval;
    if (job->delay > interval)
        job->delay = interval;
}
