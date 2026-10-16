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

static inline struct FrameObject *read_indicator(struct FrameNeedEffectState *owner)
{
    struct FrameObject *indicator;
    __builtin_memcpy(&indicator, owner->unknown_58, sizeof(indicator));
    return indicator;
}

static inline void write_indicator(struct FrameNeedEffectState *owner,
                                    struct FrameObject *indicator)
{
    __builtin_memcpy(owner->unknown_58, &indicator, sizeof(indicator));
}

unsigned int frame_step_attachment_job_45_3594c(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    if (!job->running) {
        switch ((unsigned int)job->timer) {
        case 0:
            frame_set_actor_direction(job->actor,
                g_actor_reverse_directions[owner->object->unknown_12[0]]);
            if (frame_need_effect_try_actor_effect(owner, job->actor) == 1)
                job->timer = 1;
            else {
                write_indicator(owner,
                    frame_create_attachment_parameter_indicator(job->actor, 0));
                frame_request_animation((struct FrameCommandObject *)job->actor, 46);
                job->timer = 5;
                write_sample(owner, audio_play_animation_cue(19));
            }
            break;
        case 5:
            if ((unsigned char)frame_need_effect_consume_optional(owner, job,
                    read_indicator(owner)) == 1) {
                job->timer = 1;
                resource_set_triple(0, 3, 1);
            }
            break;
        }
    } else
        job->timer = 1;
    if (job->timer == 1) {
        audio_game_stop_sample(read_sample(owner));
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        if (read_indicator(owner)) {
            transition_object_set_state(read_indicator(owner), 1);
            write_indicator(owner, 0);
        }
        return 2;
    }
    return 1;
}
