#include "frame_actor_attachment_job_12.h"

unsigned int frame_initialize_attachment_job_12(struct FrameNeedEffectState *owner)
{
    struct FrameAttachmentJob12Timers *work = (struct FrameAttachmentJob12Timers *)owner;
    work->idle_timer = 900;
    work->active_timer = 0;
#if TSBO_REVISION == 0
    owner->parameter = 0x500;
#else
    /* Revision 1 counts the parameter down and ends the idle wait at zero. */
    if ((short)owner->parameter == 0)
        owner->parameter = 0x500;
    else if ((owner->parameter -= 0x100) == 0)
        work->idle_timer = 1;
#endif
    return 1;
}
asm(".align 2, 0");
