#include "frame_actor_attachment_jobs_45_56_57.h"

unsigned int frame_select_attachment_jobs_45_56_57(struct FrameNeedEffectState *owner,
                                                   unsigned char *choices)
{
    if ((unsigned char)frame_need_effect_optional_one_ready(owner) == 0) {
        if (((struct FrameAttachmentAnimationChoice *)owner)->mode == 0x200)
            choices[0] = 57;
        else
            choices[0] = 56;
    } else {
        choices[0] = 45;
    }
    return 1;
}
asm(".align 2, 0");
