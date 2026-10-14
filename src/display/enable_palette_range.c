#include "display.h"
#include "display_palette_lifecycle.h"

void display_enable_palette_range(unsigned int incoming_index)
{
    unsigned char index = incoming_index;
    struct PaletteRangeJob *job = (struct PaletteRangeJob *)(
        index * sizeof(struct PaletteRangeJob) +
        (unsigned int)g_palette_range_jobs);
    job->flags |= 1;
    g_palette_range_enabled_mask |= 1 << index;
}
