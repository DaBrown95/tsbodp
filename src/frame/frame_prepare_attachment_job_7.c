#include "display_actor_interaction.h"
#include "frame_actor_target_jobs.h"

unsigned int frame_prepare_attachment_job_7(struct FrameNeedEffectState *owner,
                                            struct FrameObject *actor,
                                            unsigned int kind)
{
    switch (kind) {
    case 7:
        return 1;
    default:
        return 1;
    }
}
