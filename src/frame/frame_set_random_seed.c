#include "frame_random.h"

void frame_set_random_seed(unsigned int seed)
{
    g_frame_random_seed = seed;
    frame_seed_random_words(seed);
    g_frame_random_remaining = 623;
    g_frame_random_next = (unsigned int *)(g_frame_random_buffer_address + 4);
}
