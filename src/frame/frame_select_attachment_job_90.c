#include "frame_actor_attachment_jobs_45_90.h"
unsigned int frame_select_attachment_job_90(struct FrameNeedEffectState *owner,
                                           unsigned char *out)
{
    if ((unsigned char)condition_is_complete(3, 0, 0))
        out[0] = 0;
    else
        out[0] = 90;
    return 1;
}
