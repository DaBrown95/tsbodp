#include "display.h"

/* Keep each captured palette word in its two-byte value representation. */
union __attribute__((packed, aligned(2))) PaletteHalfwordInput {
    unsigned short word;
};

typedef char palette_halfword_input_size[
    (sizeof(union PaletteHalfwordInput) == 2) ? 1 : -1];
typedef char palette_halfword_input_alignment[
    (__alignof__(union PaletteHalfwordInput) == 2) ? 1 : -1];

void display_step_palette_block(struct PaletteBlockJob *job)
{
    int update;

    if (job->flags & 0x20) {
        --job->delay;
        if (job->delay == 0xff) {
            update = 1;
            job->delay = job->interval;
        } else {
            update = 0;
        }
    } else {
        update = 1;
    }

    if (job->remaining == 0) {
        if (job->flags & 0x10) {
            ++job->palette_index;
            if (job->palette_index >= job->palette_count)
                job->palette_index = 0;
            job->remaining = job->duration;
            job->target = job->palettes + job->palette_index * 16;
        } else {
            job->flags &= ~1;
            display_set_bytes(job, 0, sizeof(*job));
            if (g_palette_block_count)
                --g_palette_block_count;
        }
    } else if (update) {
        unsigned int first;
        unsigned short *output;
        const unsigned short *target;
        unsigned int count;

        if (job->flags & 4)
            output = g_palette_buffer_pairs[1].staging;
        else
            output = g_palette_buffer_pairs[0].staging;
        first = job->first;
        output += first;

        if (job->flags & 8)
            target = job->target + (first & 15);
        else
            target = job->target + first;

        count = job->count;
        if (count) {
            do {
                union PaletteHalfwordInput current_color = { *output };
                union PaletteHalfwordInput target_color = { *target };

                if (current_color.word != target_color.word) {
                    unsigned short red = current_color.word & 0x001f;
                    unsigned short green;
                    unsigned short blue;
                    int red_delta = (target_color.word & 0x001f) - red;
                    int remaining = job->remaining;

                    red += display_divide(red_delta, remaining);
                    green = (current_color.word & 0x03e0) >> 5;
                    green += display_divide(
                        ((target_color.word & 0x03e0) >> 5) - green, remaining);
                    blue = (current_color.word & 0x7c00) >> 10;
                    blue += display_divide(
                        ((target_color.word & 0x7c00) >> 10) - blue, remaining);
                    *output = (red & 0x001f) | ((green << 5) & 0x03e0) |
                        ((blue << 10) & 0x7c00);
                }

                ++output;
                ++target;
                --count;
            } while (count);
        }

        job->flags |= 2;
        --job->remaining;
    }
}
