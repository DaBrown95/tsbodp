#include "display_actor_interaction.h"
#include "frame_actor_attachment_job_18.h"

unsigned int frame_prepare_attachment_job_18(struct FrameNeedEffectState *owner,
                                            struct FrameObject *actor,
                                            unsigned int kind)
{
    switch (kind) {
    case 18:
        return 1;
    default:
        return 1;
    }
}
