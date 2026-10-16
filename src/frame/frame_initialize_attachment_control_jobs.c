#include "frame_actor_attachment_control_jobs.h"

unsigned int frame_initialize_attachment_control_jobs(struct FrameNeedEffectState *owner)
{
    if ((short)owner->parameter != 0)
        frame_refresh_attachment_control_174a8(owner);
    return 1;
}
asm(".align 2, 0");
