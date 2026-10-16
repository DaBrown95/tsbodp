#include "frame_actor_attachment_palette_jobs.h"

unsigned int frame_prepare_attachment_palette_jobs(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor,
                                                    unsigned int kind)
{
    switch (kind) {
    case 8:
    case 9:
    case 10:
    case 11:
        return 1;
    default:
        return 1;
    }
}
