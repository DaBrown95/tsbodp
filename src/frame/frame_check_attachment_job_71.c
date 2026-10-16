#include "frame_actor_attachment_job_71.h"

unsigned int frame_check_attachment_job_71(struct FrameNeedEffectState *owner,
                                          struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2, 0");
