#include "display.h"
void display_load_palette_ranges(const struct PaletteRangeConfig *config)
{
    int index = 0;
    const struct PaletteRangeConfigEntry *entry;
    if (index < config->count) {
    unsigned int zero = index;
    unsigned int *enabled_mask = &g_palette_range_enabled_mask;
    entry = config->entries;
    do {
        unsigned int first = entry->first;
        unsigned int count = entry->count;
        unsigned int delay = entry->delay;
        unsigned int flags = entry->flags;
        struct PaletteRangeJob *job = &g_palette_range_jobs[display_next_palette_range()];
        job->flags = flags;
        job->interval = delay;
        job->delay = zero;
        job->source_first = first;
        job->destination_first = first;
        first += count;
        --first;
        job->destination_last = first;
        job->count = count;
        job->original_count = count;
        *enabled_mask |= 1 << index;
        ++entry;
        ++index;
    } while(index < config->count);
    }
}
