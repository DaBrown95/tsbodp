#include "display.h"
#include "display_palette_lifecycle.h"

void display_step_palette_ranges(void)
{
    unsigned int index = 0;
    do {
        struct PaletteRangeJob *job = &g_palette_range_jobs[index];
        if (job->flags & 1)
            display_step_palette_range(job);
        ++index;
    } while (index <= 11);
}
