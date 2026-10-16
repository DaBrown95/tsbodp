#include "frame_actor_attachment_jobs_64_66.h"

unsigned int frame_initialize_attachment_jobs_64_66(struct FrameNeedEffectState *owner)
{
    if (*(short *)&owner->parameter == 0x5000)
        ((struct FrameNeedEffectObject *)owner->object)->requested_animation = 3;
    else if (*(short *)&owner->parameter == 0x2800)
        ((struct FrameNeedEffectObject *)owner->object)->requested_animation = 1;
    else {
        ((struct FrameNeedEffectObject *)owner->object)->requested_animation = 0;
        owner->parameter = 0;
        owner->optional = 0;
    }
    return 1;
}
