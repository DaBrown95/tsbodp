#include "frame_actor_attachment_jobs_60_63.h"
void frame_tick_attachment_jobs_60_63(struct FrameNeedEffectState *owner)
{
    struct FrameAttachmentRecoveryWork *work = (struct FrameAttachmentRecoveryWork *)owner;
    if ((short)owner->parameter <= 0x4ff) {
        if (--work->countdown == 65535) {
            if ((short)owner->parameter <= 0x4ff) {
                owner->parameter += 0x100;
                work->countdown = 3600;
            } else if (owner->object->unknown_0a == 15) {
                frame_set_animation_frame((struct FrameTickObject *)owner->object, 1);
            }
        }
    } else if (work->settled && owner->object->unknown_0a == 15) {
        work->settled = 0;
        frame_set_animation_frame((struct FrameTickObject *)owner->object, 1);
    }
}
asm(".align 2,0");
