#include "frame_shared_optional_jobs.h"
unsigned int frame_shared_optional_choices(struct FrameNeedEffectState *owner,unsigned char *choices)
{
 if (!(unsigned char)frame_need_effect_optional_one_ready(owner)) *choices=61;
 else *choices=45;
 return 1;
}
asm(".align 2, 0");
