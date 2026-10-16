#include "frame_actor_attachment_jobs_45_56_57.h"

unsigned int frame_step_attachment_modes_56_57_23ec4(struct FrameNeedEffectState *owner,
                                                   struct FrameActorAttachmentRecord *job,
                                                   unsigned int mode)
{
    struct FrameObject *actor = job->actor;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_need_effect_try_optional(owner);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        ((struct FrameAttachmentAnimationChoice *)owner)->mode = mode;
        job->timer = 57;
        audio_play_animation_cue(175);
        break;
    case 57:
        if (actor->flags & 0x400000) {
            if (mode == 0x100)
                frame_commit_need_effect(owner->object, 3);
            else
                frame_commit_need_effect(owner->object, 2);
            job->timer = 1;
        }
        break;
    }
    if (job->timer == 1)
        return 2;
    return 1;
}
asm(".align 2, 0");
