#include "frame_actor_attachment_jobs.h"

int frame_random_range(int first, int last)
{
    if (first == last) return first;
    {
        int value = frame_next_random_word();
        value &= 0x7fff;
        return first + (((last - first + 1) * value) >> 15);
    }
}
