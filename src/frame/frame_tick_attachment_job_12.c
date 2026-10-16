#include "frame_actor_attachment_job_12.h"

void frame_tick_attachment_job_12(struct FrameNeedEffectState *owner)
{
    struct FrameAttachmentJob12Timers *work = (struct FrameAttachmentJob12Timers *)owner;
    if (owner->parameter <= 0x500)
        frame_set_animation_frame((struct FrameTickObject *)owner->object, owner->parameter >> 8);
    if (--work->idle_timer == -1) {
        if ((short)owner->parameter > 0) {
            owner->parameter -= 0x100;
            work->idle_timer = 900;
        } else
            transition_object_set_state(owner->object, 1);
    }
}
asm(".align 2,0");
