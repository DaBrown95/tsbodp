#include "frame_shared_optional_jobs.h"
unsigned int frame_shared_optional_attachment_check(struct FrameNeedEffectState *owner,
                                                        struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2, 0");
