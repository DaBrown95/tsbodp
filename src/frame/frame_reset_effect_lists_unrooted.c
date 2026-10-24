#include "frame_render_effect.h"
#include "frame_transient_effect.h"

void frame_reset_effect_lists_unrooted_30f70(void)
{
    int group = 0;
    register unsigned int work asm("r0") = (unsigned int)g_frame_transient_definitions;
    register unsigned short *first asm("r5") = (unsigned short *)(work + 36);
    register unsigned short invalid asm("r4");

    work = 0xffff;
    invalid = work;
    do {
        int next_group;
        unsigned short *index;
        int remaining;

        work = group * 4;
        next_group = group + 1;
        work = (work + group) * 64;
        index = (unsigned short *)(work + (unsigned int)first);
        remaining = 7;
        do {
            {
                register unsigned short value asm("r0") = *index;
                value |= invalid;
                *index = value;
            }
            index = (unsigned short *)((unsigned int)index + 40);
        } while (--remaining >= 0);
        group = next_group;
    } while (group <= 0);
    frame_clear_transient_effects();
    frame_clear_render_effects();
}
