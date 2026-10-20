#include "frame_optional_activation.h"

unsigned int frame_step_optional_activation_job_82_86(struct FrameNeedEffectState *owner,
    struct FrameActorAttachmentRecord *job, unsigned char variant)
{
    unsigned int result = 1;

    switch ((unsigned int)job->timer) {
    case 0:
        ((struct FrameActorObject *)job->actor)->direction =
            frame_direction_to_need_effect_center(job->actor, owner);
        job->timer = 85;
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        owner->optional_sample = audio_play_animation_cue(63);
        break;
    case 85:
        if (job->actor->flags & 0x400000) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            job->timer = 1;
            if (variant == 0) {
                frame_commit_need_effect(owner->object, 3);
                ((struct FrameOptionalChoiceContextState *)owner)->active = 1;
            } else {
                frame_commit_need_effect(owner->object, 2);
                ((struct FrameOptionalChoiceContextState *)owner)->active = 0;
            }
        }
        break;
    case 1:
        audio_game_stop_sample(owner->optional_sample);
        result = 2;
        break;
    }
    return result;
}
