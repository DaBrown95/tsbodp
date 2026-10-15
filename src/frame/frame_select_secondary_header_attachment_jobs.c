#include "frame_need_effect_secondary_header_jobs.h"
unsigned int frame_select_secondary_header_attachment_jobs(struct FrameNeedEffectState *owner,unsigned char *choices)
{
 choices[0]=50;
 if((short)owner->parameter==2560&&owner->kind!=84&&!((struct FrameSecondaryHeaderOwnerWork *)owner)->active)choices[1]=27;
 return 1;
}
asm(".align 2, 0");
