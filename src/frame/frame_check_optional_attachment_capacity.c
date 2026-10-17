#include "frame_need_effect_optional_jobs.h"

unsigned int frame_check_optional_attachment_capacity(struct FrameNeedEffectState *owner,
                                                        struct FrameObject *actor)
{
    unsigned int count = 0, i;
    struct FrameNeedEffectState *view = owner;
    for (i = 0; i < 3; i++)
        if (view->records[i].actor)
            count++;
    if (count >= owner->unknown_58[5])
        return 0;
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2, 0");
