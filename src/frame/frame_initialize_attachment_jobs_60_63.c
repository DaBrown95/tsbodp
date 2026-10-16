#include "frame_actor_attachment_jobs_60_63.h"
unsigned int frame_initialize_attachment_jobs_60_63(struct FrameNeedEffectState *owner)
{
    if ((short)owner->parameter == 0) owner->parameter = 0x100;
    if ((short)owner->parameter == 0x500 && owner->kind == 15)
        ((struct FrameAttachmentRecoveryWork *)owner)->settled = 1;
    ((struct FrameAttachmentRecoveryWork *)owner)->countdown = 3600;
    return 1;
}
