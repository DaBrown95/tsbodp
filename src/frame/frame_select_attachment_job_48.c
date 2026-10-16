#include "display_actor_interaction.h"
#include "frame_actor_attachment_job_48.h"

unsigned int frame_select_attachment_job_48(struct FrameNeedEffectState *owner,
                                           unsigned char *choices)
{
    choices[0] = 48;
    return 1;
}
