#include "display.h"
void display_step_palette_range(struct PaletteRangeJob *job)
{
    if (!job->delay) {
        if (job->flags & 0x20) {
            if (job->destination_first == job->source_first) job->destination_first = job->destination_last;
            else --job->destination_first;
        } else {
            if (job->destination_first == job->destination_last) job->destination_first = job->source_first;
            else ++job->destination_first;
        }
        if (job->flags & 0x10) {
            if (job->flags & 0x20) {
                if (job->destination_first == job->source_first) job->flags ^= 0x20;
            } else if (job->destination_first == job->destination_last) job->flags ^= 0x20;
        }
        job->flags |= 2;
        job->delay = job->interval;
    } else --job->delay;
}
__asm__(".align 2, 0");
