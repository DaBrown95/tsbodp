#include "display.h"
#include "display_palette_lifecycle.h"

unsigned int display_create_palette_sequence_config(
    const struct PaletteSequenceConfig *config, unsigned int flags,
    unsigned int palette_count)
{
    unsigned int index = display_create_palette_block(config->first,
        config->count, config->duration, config->interval, flags,
        config->palettes);
    struct PaletteBlockJob *job = (struct PaletteBlockJob *)(
        index * sizeof(struct PaletteBlockJob) +
        (unsigned int)g_palette_block_jobs);
    job->palette_count = palette_count;
    return index;
}
