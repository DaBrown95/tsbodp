#include "display.h"
#include "display_palette_lifecycle.h"

void display_reset_palette_ranges(void)
{
    unsigned int index;
    struct PaletteRangeJob *job;
    g_palette_range_count = 0;
    index = 0;
    job = g_palette_range_jobs;
    do {
        display_reset_palette_range(job);
        ++job;
        ++index;
    } while (index <= 11);
}
