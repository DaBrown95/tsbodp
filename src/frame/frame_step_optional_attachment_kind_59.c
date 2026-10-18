#include "frame_optional_attachment_jobs_12_45_59.h"

unsigned int frame_step_optional_attachment_kind_59(struct FrameNeedEffectState *owner,
                                                   struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs =
        ((struct FrameActorObject *)job->actor)->actor_state;
    unsigned int result = 1;

    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_need_effect_try_optional(owner);
        frame_need_effect_accumulate_optional(owner);
        ((struct FrameActorObject *)job->actor)->direction =
            ((struct FrameActorObject *)owner->object)->direction;
        job->timer = 46;
        ((struct FrameActorStateWork *)job->actor)->timer = 90;
        if ((unsigned char)
            (((struct FrameActorObject *)owner->object)->direction - 3) <= 2)
            frame_request_animation((struct FrameCommandObject *)job->actor, 57);
        else
            frame_request_animation((struct FrameCommandObject *)job->actor, 50);
        break;
    case 46:
        if (job->actor->flags & 0x400000) {
            frame_clear_animation_pending(job->actor);
            job->timer = 47;
        }
        break;
    case 47:
        frame_adjust_actor_needs(needs, 29,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (!(unsigned char)frame_step_attachment_need_timer(job, needs, 5,
                &((struct FrameActorStateWork *)job->actor)->timer)) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        }
        break;
    case 1:
        audio_play_animation_cue(164);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
