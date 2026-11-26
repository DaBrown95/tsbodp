#include "frame_need_effect_optional_activity.h"

/* The actual F8 driver passes state; this callback performs no operation. */
void frame_optional_activity_tick(struct FrameNeedEffectState *owner)
{
    (void)owner;
}
asm(".align 2, 0");
