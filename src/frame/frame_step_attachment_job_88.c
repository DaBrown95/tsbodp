#include "frame_actor_attachment_jobs_88_89.h"

static inline unsigned int read_sample(struct FrameNeedEffectState *owner)
{
    struct DisplayNeedEffectStateView *storage = (struct DisplayNeedEffectStateView *)owner;
    unsigned int sample;
    __builtin_memcpy(&sample, &storage->unknown_dd[3], sizeof(sample));
    return sample;
}

static inline void write_sample(struct FrameNeedEffectState *owner, unsigned int sample)
{
    struct DisplayNeedEffectStateView *storage = (struct DisplayNeedEffectStateView *)owner;
    __builtin_memcpy(&storage->unknown_dd[3], &sample, sizeof(sample));
}

unsigned int frame_step_attachment_job_88(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs;
    unsigned int result;
    __builtin_memcpy(&needs, &job->actor->motion_storage.bytes[20], sizeof(needs));
    result = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[owner->object->unknown_12[0]]);
        job->timer = 6;
        if (frame_gate_attachment_game_value(owner, job, 10) == 1) {
            frame_need_effect_try_optional(owner);
            frame_need_effect_accumulate_optional(owner);
            frame_request_animation((struct FrameCommandObject *)job->actor, 58);
            audio_play_animation_cue(170);
        } else {
            frame_request_animation((struct FrameCommandObject *)job->actor, 5);
            if (g_frame_interaction_settings.attachment_mode == 0)
                audio_play_animation_cue(86);
            else
                audio_play_animation_cue(85);
            job->timer = 8;
        }
        break;
    case 8:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    case 6:
        if (job->actor->flags & 0x400000) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            frame_commit_need_effect(owner->object, 1);
            audio_play_animation_cue(171);
            job->timer = 7;
            job->actor->motion_storage.motion.timer = 30;
        }
        break;
    case 7:
        if (--job->actor->motion_storage.motion.timer == 0xFFFF) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 21);
            frame_commit_need_effect(owner->object, 2);
            write_sample(owner, audio_play_animation_cue(21));
            job->timer = 27;
        }
        break;
    case 27:
        frame_adjust_actor_needs(needs, 40,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (job->actor->flags & 0x400000) {
            audio_game_stop_sample(read_sample(owner));
            job->timer = 9;
        }
        break;
    case 9:
        audio_game_stop_sample(read_sample(owner));
        if (g_frame_interaction_settings.attachment_mode == 0)
            audio_play_animation_cue(146);
        else
            audio_play_animation_cue(145);
        job->timer = 1;
        break;
    case 1:
        frame_commit_need_effect(owner->object, 0);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2, 0");
