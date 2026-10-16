#include "frame_parameter_stage_jobs.h"

unsigned int frame_parameter_stage_percentage(struct FrameNeedEffectState *owner)
{
    unsigned int result = 100;
    if ((short)owner->parameter == 0)
        result = 50;
    return result;
}
asm(".align 2,0");
