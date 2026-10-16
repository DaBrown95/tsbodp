#include "frame_actor_attachment_jobs_79_80.h"

unsigned int frame_select_attachment_jobs_79_80(struct FrameNeedEffectState *owner,
                                               unsigned char *choices)
{
    choices[0] = 79;
    if (frame_read_signed_parameter(g_frame_actor_social_probe, 4) != 10)
        choices[1] = 80;
    return 1;
}
