#include "display_actor_interaction.h"
#include "frame_actor_attachment_job_70.h"

unsigned int frame_select_attachment_job_70(struct FrameNeedEffectState *owner,
                                           unsigned char *choices)
{
    choices[0] = 70;
    return 1;
}
