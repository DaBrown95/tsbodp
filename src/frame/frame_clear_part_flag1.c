#include "frame_animation.h"

/* Native low-byte selection; sufficient backing remains a caller obligation. */
void frame_clear_part_flag1(void *base, unsigned int part)
{
    unsigned char *flags = (unsigned char *)base +
        (unsigned char)part * sizeof(struct FrameAnimationPart) + 0x104;

    *flags &= ~2u;
}
