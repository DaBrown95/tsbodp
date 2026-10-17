#include "frame_optional_three_effect.h"

unsigned int frame_check_optional_three_effect_count(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2,0");
