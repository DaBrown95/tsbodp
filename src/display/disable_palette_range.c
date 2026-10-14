#include "display.h"
#include "display_palette_lifecycle.h"

void display_disable_palette_range(unsigned int incoming_index,
    unsigned int incoming_restore)
{
    unsigned char index = incoming_index, restore = incoming_restore;
    struct PaletteRangeJob *job = &g_palette_range_jobs[index];
    job->flags &= ~1;
    g_palette_range_enabled_mask &= ~(1 << index);
    if (restore) {
        job->destination_first = job->source_first;
        job->flags |= 2;
    }
}
