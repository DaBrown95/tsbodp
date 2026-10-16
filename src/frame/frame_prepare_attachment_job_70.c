#include "display_actor_interaction.h"
#include "frame_actor_attachment_job_70.h"

unsigned int frame_prepare_attachment_job_70(struct FrameNeedEffectState *owner,
                                            struct FrameObject *actor,
                                            unsigned int kind)
{
    switch (kind) {
    case 70:
        return 1;
    default:
        return 1;
    }
}
