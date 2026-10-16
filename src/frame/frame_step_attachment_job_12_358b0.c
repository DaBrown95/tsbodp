#include "frame_actor_attachment_jobs_12_31_33_45.h"

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

static inline struct FrameActorNeedState *read_needs(struct FrameObject *actor)
{
    struct FrameActorNeedState *needs;
    __builtin_memcpy(&needs, &actor->motion_storage.bytes[20], sizeof(needs));
    return needs;
}

unsigned int frame_step_attachment_job_12_358b0(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[owner->object->unknown_12[0]]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 14);
        job->timer = 4;
        write_sample(owner, audio_play_animation_cue(26));
        break;
    case 4:
        frame_adjust_actor_needs(read_needs(job->actor), 52,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_need_effect_consume_optional_two(owner) == 1)
            job->timer = 1;
        break;
    case 1:
        audio_game_stop_sample(read_sample(owner));
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
