#include "frame_actor_attachment_sequence_jobs.h"

unsigned int frame_check_attachment_sequence_jobs(struct FrameNeedEffectState *owner,
                                                  struct FrameObject *actor,
                                                  unsigned int kind)
{
    switch (kind) {
    case 2:
    case 5:
    case 18:
    case 45:
    case 56:
    case 57:
        return 1;
    default:
        return 1;
    }
}
asm(".align 2, 0");
