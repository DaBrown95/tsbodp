#include "display.h"
#include "display_palette_lifecycle.h"

unsigned int display_create_palette_sequence(unsigned int first,
    unsigned int count, unsigned int duration, unsigned int interval,
    unsigned int flags, const unsigned short *palettes,
    unsigned int palette_count)
{
    unsigned int index = display_create_palette_block(first, count, duration,
        interval, flags, palettes);
    struct PaletteBlockJob *job = (struct PaletteBlockJob *)(
        index * sizeof(struct PaletteBlockJob) +
        (unsigned int)g_palette_block_jobs);
    job->palette_count = palette_count;
    return index;
}
