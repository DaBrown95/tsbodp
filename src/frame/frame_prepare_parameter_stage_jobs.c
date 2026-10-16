#include "frame_parameter_stage_jobs.h"

unsigned int frame_prepare_parameter_stage_jobs(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor,
                                                  unsigned int kind)
{
    switch (kind) {
    case 7:
    case 91:
        return 1;
    default:
        return 1;
    }
}
