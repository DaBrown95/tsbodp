#include "frame_actor_attachment_job_12.h"

unsigned int frame_step_attachment_job_12_34bf4(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    struct FrameAttachmentJob12Timers *work = (struct FrameAttachmentJob12Timers *)owner;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_stop_motion(job->actor);
        job->timer = 48;
        frame_set_actor_direction(job->actor,
            frame_direction_to_need_effect_center(job->actor, owner));
        frame_request_animation((struct FrameCommandObject *)job->actor, 27);
        audio_play_animation_cue(71);
        work->active_timer = 30;
        ((struct FrameActorStateWork *)job->actor)->timer = 0;
        break;
    case 48:
        frame_adjust_actor_needs(((struct FrameActorObject *)job->actor)->actor_state,
            52, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (++((struct FrameActorStateWork *)job->actor)->timer == 43) {
            ((struct FrameAttachmentJobWork *)owner)->sample = audio_play_animation_cue(71);
            ((struct FrameActorStateWork *)job->actor)->timer = 0;
        }
        if (--work->active_timer == -1) {
            if ((short)owner->parameter > 0) {
                owner->parameter -= 0x100;
                work->active_timer = 30;
            } else {
                transition_object_set_state(owner->object, 1);
                job->timer = 1;
                frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            }
        }
        break;
    }
    if (job->timer == 1) return 2;
    return 1;
}
asm(".align 2,0");
