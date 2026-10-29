#include "frame_animation.h"

/* Native byte selection/store; sufficient backing remains a caller obligation. */
void frame_set_part_palette(void *base, unsigned int part, unsigned int palette)
{
    unsigned char *palette_byte = (unsigned char *)base +
        (unsigned char)part * sizeof(struct FrameAnimationPart) + 0x105;

    *palette_byte = (unsigned char)palette;
}
