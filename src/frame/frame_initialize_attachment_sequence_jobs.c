#include "frame_actor_attachment_sequence_jobs.h"

unsigned int frame_initialize_attachment_sequence_jobs(struct FrameNeedEffectState *owner)
{
    if ((short)owner->parameter != 0)
        frame_refresh_attachment_sequence_41c18(owner);
    return 1;
}
asm(".align 2, 0");
