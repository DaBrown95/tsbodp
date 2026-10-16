#include "frame_actor_attachment_jobs_16_17.h"

unsigned int frame_select_attachment_jobs_16_17(struct FrameNeedEffectState *owner,
                                                unsigned char *choices)
{
    choices[0] = 16;
    choices[1] = 17;
    return 1;
}
