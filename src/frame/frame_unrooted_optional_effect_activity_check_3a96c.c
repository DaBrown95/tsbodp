#include "frame_optional_effect_activity_jobs.h"
unsigned int frame_unrooted_optional_effect_activity_check_3a96c(struct FrameNeedEffectState *owner,
                                                   struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2,0");
