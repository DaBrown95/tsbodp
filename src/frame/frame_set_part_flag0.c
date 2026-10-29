#include "frame_animation.h"

/* A byte view of the observed flags field; no record-array bound is implied. */
struct __attribute__((packed)) FramePartFlagByte { unsigned char flags; };

typedef char flag_byte_size[(sizeof(struct FramePartFlagByte) == 1) ? 1 : -1];
typedef char flag_byte_alignment[
    (__alignof__(struct FramePartFlagByte) == 1) ? 1 : -1];

/* Native low-byte selection; sufficient backing remains a caller obligation. */
void frame_set_part_flag0(void *base, unsigned int part)
{
    struct FramePartFlagByte *selected = (struct FramePartFlagByte *)
        ((unsigned char *)base +
         (unsigned char)part * sizeof(struct FrameAnimationPart) + 0x104);

    selected->flags |= 1;
}
