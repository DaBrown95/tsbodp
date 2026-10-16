#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_attachment_jobs_60_63_percentage(struct FrameNeedEffectState *owner)
{
    unsigned int result;
    if ((short)owner->parameter == 0x500) result = 0;
    else result = 100;
    return result;
}
asm(".align 2,0");
