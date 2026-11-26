#include "frame_optional_attachment_dispatch.h"

/* Row-two callback: the state argument is unused in this body. */
void frame_optional_attachment_tick(struct FrameNeedEffectState *owner)
{
    (void)owner;
}
asm(".align 2, 0");
