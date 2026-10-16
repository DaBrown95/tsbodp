#include "frame_actor_attachment_job_87.h"

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

static inline int read_actor_timer(struct FrameObject *actor)
{
    int timer;
    __builtin_memcpy(&timer, &actor->motion_storage.bytes[12], sizeof(timer));
    return timer;
}

static inline void write_actor_timer(struct FrameObject *actor, int timer)
{
    __builtin_memcpy(&actor->motion_storage.bytes[12], &timer, sizeof(timer));
}

unsigned int frame_step_attachment_job_87(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    struct FrameActorNeedState *needs;
    unsigned int result;
    int previous;

    __builtin_memcpy(&needs, &job->actor->motion_storage.bytes[20], sizeof(needs));
    result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        if (frame_attachment_need_is_low(needs, 8) == 1) {
            frame_set_actor_direction(job->actor, 4);
            frame_request_animation((struct FrameCommandObject *)job->actor, 85);
            if (g_attachment_job_87_world.attachment_mode == 0)
                audio_play_animation_cue(137);
            else
                audio_play_animation_cue(136);
            job->timer = 8;
            break;
        }
        previous = frame_read_signed_parameter(g_attachment_job_87_world.parameters,
            g_attachment_job_87_parameter_indices[owner->optional - 4]);
        write_indicator(owner, 0);
        if (previous != 10) {
            write_indicator(owner,
                frame_create_attachment_parameter_indicator(job->actor, 1));
            job->actor->unknown_12[0] =
                frame_direction_to_need_effect_center(job->actor, owner);
        }
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[owner->object->unknown_12[0]]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 54);
        job->timer = 72;
        if (g_attachment_job_87_world.attachment_mode == 0)
            audio_play_animation_cue(133);
        else
            audio_play_animation_cue(132);
        write_actor_timer(job->actor, 150);
        break;
    case 72:
        previous = frame_read_signed_parameter(g_attachment_job_87_world.parameters,
            g_attachment_job_87_parameter_indices[owner->optional - 4]);
        if (previous != 10) {
            unsigned char percentage = frame_read_parameter_percentage(
                g_attachment_job_87_world.parameters,
                g_attachment_job_87_parameter_indices[owner->optional - 4]);
            int current;
            frame_set_attachment_parameter_indicator(read_indicator(owner), percentage);
            frame_update_attachment_parameter(g_attachment_job_87_world.parameters,
                g_attachment_job_87_parameter_indices[owner->optional - 4],
                read_indicator(owner));
            frame_adjust_actor_needs(needs, 35,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
            current = frame_read_signed_parameter(g_attachment_job_87_world.parameters,
                g_attachment_job_87_parameter_indices[owner->optional - 4]);
            if (current == previous + 1 || current == 10)
                job->timer = 1;
        } else {
            int timer = read_actor_timer(job->actor) - 1;
            write_actor_timer(job->actor, timer);
            if (timer == -1)
                job->timer = 1;
        }
        break;
    case 8:
        if (job->actor->flags & 0x400000) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            frame_clear_attachment_need_countdown(needs);
        }
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        if (read_indicator(owner)) {
            transition_object_set_state(read_indicator(owner), 1);
            write_indicator(owner, 0);
        }
        result = 2;
        break;
    }
    return result;
}
asm(".align 2, 0");
