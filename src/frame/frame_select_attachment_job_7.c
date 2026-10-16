#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"

unsigned int frame_select_attachment_job_7(struct FrameNeedEffectState *owner,
                                           unsigned char *choices)
{
    choices[0] = 7;
    return 1;
}
