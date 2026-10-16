#include "frame_actor_attachment_jobs_64_66.h"

unsigned char frame_attachment_jobs_64_66_percentage(struct FrameNeedEffectState *owner)
{
    unsigned char result = 100;
    if ((short)owner->parameter == 0)
        result = 50;
    return result;
}
asm(".align 2, 0");
