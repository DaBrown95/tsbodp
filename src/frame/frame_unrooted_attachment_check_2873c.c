#include "frame_unrooted_attachment_checks.h"

unsigned int frame_unrooted_attachment_check_2873c(struct FrameNeedEffectState *owner,
                                             struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2,0");
