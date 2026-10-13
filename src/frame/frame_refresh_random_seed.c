#include "frame_random.h"
#include "irq.h"
#include "input.h"

void frame_refresh_random_seed(void)
{
    unsigned int count;

    g_frame_random_remaining = -1;
    g_frame_random_secondary_remaining = -1;
    g_frame_random_seed += (g_irq_context->vblank_count << 4) +
                          (g_input_current[0] << 2);
    if (!g_frame_random_seed)
        g_frame_random_seed = (frame_next_random_word() % 0xfff1f) + 1;
    count = ++g_frame_random_seed_refresh_count;
    g_frame_random_seed = ((g_frame_random_seed << 8) +
                          (g_irq_context->vblank_count << 6) + (count << 4)) |
                         g_input_current[0];
    frame_seed_random_words(g_frame_random_seed);
}
