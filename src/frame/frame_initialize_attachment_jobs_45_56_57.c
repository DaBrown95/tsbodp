#include "frame_actor_attachment_jobs_45_56_57.h"

unsigned int frame_initialize_attachment_jobs_45_56_57(struct FrameNeedEffectState *owner)
{
    if (owner->optional != 1) {
        if (((struct FrameAttachmentAnimationChoice *)owner)->mode == 0x200)
            ((struct FrameNeedEffectObject *)owner->object)->requested_animation = 2;
        else
            ((struct FrameNeedEffectObject *)owner->object)->requested_animation = 3;
    }
    return 1;
}
