#include "frame_actor_attachment_jobs_3_4_18.h"

unsigned int frame_select_attachment_jobs_3_4_18(struct FrameNeedEffectState *owner,
                                                unsigned char *choices)
{
    struct FrameAttachmentSequenceMode *work = (struct FrameAttachmentSequenceMode *)owner;
    unsigned int index;
    choices[0] = 18;
    index = 1;
    if (work->enabled != 1) {
        choices[1] = 3;
        index = 2;
    }
    if (work->enabled != 0)
        choices[index] = 4;
    return 1;
}
