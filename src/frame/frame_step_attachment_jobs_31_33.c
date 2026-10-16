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

static inline unsigned int read_second_sample(struct FrameNeedEffectState *owner)
{
    unsigned int sample;
    __builtin_memcpy(&sample, &owner->unknown_63[1], sizeof(sample));
    return sample;
}

static inline void write_second_sample(struct FrameNeedEffectState *owner,
                                        unsigned int sample)
{
    __builtin_memcpy(&owner->unknown_63[1], &sample, sizeof(sample));
}

unsigned int frame_step_attachment_jobs_31_33(struct FrameNeedEffectState *owner,
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
        if ((unsigned char)condition_is_complete(0, 4, 0)) {
            if (frame_gate_attachment_game_value(owner, job,
                    g_frame_world_id == 28 ? 20 : 10) == 1) {
                frame_need_effect_try_optional(owner);
                frame_need_effect_accumulate_optional(owner);
            } else {
                frame_request_animation((struct FrameCommandObject *)job->actor, 5);
                if (g_frame_interaction_settings.attachment_mode == 0)
                    audio_play_animation_cue(86);
                else
                    audio_play_animation_cue(85);
                job->timer = 8;
            }
        }
        break;
    case 8:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    case 6:
        frame_commit_need_effect(owner->object, 1);
        audio_play_animation_cue(167);
        owner->object->motion_storage.bytes[3] |= 4;
        job->timer = 24;
        break;
    case 24:
        if (owner->object->flags & 0x400000) {
            frame_commit_need_effect(owner->object, 3);
            frame_request_animation((struct FrameCommandObject *)job->actor, 23);
            write_sample(owner, audio_play_animation_cue(20));
            write_second_sample(owner, audio_play_animation_cue(168));
            job->actor->motion_storage.motion.timer = 60;
            job->timer = 26;
        }
        break;
    case 26:
        frame_adjust_actor_needs(needs, 8,
            g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (job->running == 1 || --job->actor->motion_storage.motion.timer == 0xFFFF)
            job->timer = 9;
        break;
    case 9:
        frame_commit_need_effect(owner->object, 2);
        audio_game_stop_sample(read_sample(owner));
        audio_game_stop_sample(read_second_sample(owner));
        audio_play_animation_cue(169);
        frame_set_actor_direction(job->actor, 4);
        job->timer = 1;
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        resource_set_triple(0, 1, 0);
        result = 2;
        break;
    }
    return result;
}
