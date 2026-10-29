#include "frame.h"

/* Native byte access; sufficient backing remains a caller obligation. */
void frame_clear_sharing_flag40(void *base)
{
    FrameU8 *sharing_flags = (FrameU8 *)base + 0x101;

    *sharing_flags &= ~0x40u;
}
