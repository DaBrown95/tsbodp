#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_select_attachment_jobs_60_63(struct FrameNeedEffectState *owner,
                                                unsigned char *out)
{
    out[0] = 60;
    out[1] = 63;
    return 1;
}
