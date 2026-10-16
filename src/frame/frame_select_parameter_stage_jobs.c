#include "frame_parameter_stage_jobs.h"

unsigned int frame_select_parameter_stage_jobs(struct FrameNeedEffectState *owner,
                                                 unsigned char *choices)
{
    if ((short)owner->parameter == 0x6400)
        choices[0] = 7;
    else
        choices[0] = 91;
    return 1;
}
