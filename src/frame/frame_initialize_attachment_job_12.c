#include "frame_actor_attachment_job_12.h"

unsigned int frame_initialize_attachment_job_12(struct FrameNeedEffectState *owner)
{
    struct FrameAttachmentJob12Timers *work = (struct FrameAttachmentJob12Timers *)owner;
    work->idle_timer = 900;
    work->active_timer = 0;
    owner->parameter = 0x500;
    return 1;
}
asm(".align 2,0");
