#include "frame_actor_attachment_jobs_64_66.h"

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

static inline unsigned short decrement_countdown(struct FrameObject *actor)
{
    return --actor->motion_storage.motion.timer;
}

unsigned int frame_step_attachment_jobs_64_65(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    unsigned char percentage;
    int current;
    struct FrameActorNeedState *needs;
    unsigned int result;
    int previous;

    __builtin_memcpy(&needs, &job->actor->motion_storage.bytes[20], sizeof(needs));
    result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[owner->object->unknown_12[0]]);
        job->timer = 6;
        job->actor->motion_storage.motion.timer = 1800;
        if (frame_attachment_need_is_low(needs, 8) == 1) {
            frame_set_actor_direction(job->actor, 4);
            frame_request_animation((struct FrameCommandObject *)job->actor, 85);
            if (g_attachment_job_87_world.attachment_mode == 0)
                audio_play_animation_cue(137);
            else
                audio_play_animation_cue(136);
            job->timer = 8;
        } else if (job->kind == 65) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 49);
            job->actor->motion_storage.motion.timer = 90;
            job->timer = 3;
        }
        break;
    case 8:
        if (job->actor->flags & 0x400000) {
            job->timer = 1;
            frame_request_animation((struct FrameCommandObject *)job->actor, 1);
            frame_clear_attachment_need_countdown(needs);
        }
        break;
    case 3:
        if (decrement_countdown(job->actor) == 0xFFFF) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 28);
            job->timer = 6;
        }
        break;
    case 6:
        if (g_attachment_job_87_world.attachment_mode == 0)
            audio_play_animation_cue(133);
        else
            audio_play_animation_cue(132);
        if (job->kind == 65) {
            frame_request_animation((struct FrameCommandObject *)job->actor, 28);
            job->actor->motion_storage.motion.timer = 90;
            job->timer = 74;
        } else {
            frame_request_animation((struct FrameCommandObject *)job->actor, 28);
            job->actor->motion_storage.motion.timer = 90;
            job->timer = 73;
        }
        previous = frame_read_signed_parameter(g_attachment_job_87_world.parameters, 2);
        write_indicator(owner, 0);
        if (previous != 10) {
            write_indicator(owner,
                frame_create_attachment_parameter_indicator(job->actor, 1));
            job->actor->unknown_12[0] =
                frame_direction_to_need_effect_center(job->actor, owner);
        } else
            job->actor->motion_storage.motion.timer = 1800;
        break;
    case 74:
        previous = frame_read_signed_parameter(g_attachment_job_87_world.parameters, 2);
        if (frame_attachment_need_is_low(needs, 8) == 1)
            job->timer = 1;
        else if (previous == 10)
            frame_adjust_actor_needs(needs, 2,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        else
            frame_adjust_actor_needs(needs, 35,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned int)previous <= 9) {
            percentage = frame_read_parameter_percentage(
                g_attachment_job_87_world.parameters, 2);
            frame_set_attachment_parameter_indicator(read_indicator(owner), percentage);
            frame_update_attachment_parameter(g_attachment_job_87_world.parameters, 2,
                read_indicator(owner));
            current = frame_read_signed_parameter(g_attachment_job_87_world.parameters, 2);
            if (current == previous + 1) {
                frame_commit_need_effect(owner->object, 3);
                owner->parameter = 0x5000;
                job->timer = 1;
            }
        } else if (previous == 10) {
            if (decrement_countdown(job->actor) == 0xFFFF) {
                frame_commit_need_effect(owner->object, 3);
                owner->parameter = 0x5000;
                job->timer = 1;
            }
        }
        break;
    case 73:
        previous = frame_read_signed_parameter(g_attachment_job_87_world.parameters, 2);
        if (previous == 10)
            frame_adjust_actor_needs(needs, 2,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        else
            frame_adjust_actor_needs(needs, 35,
                g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if (frame_attachment_need_is_low(needs, 8) == 1)
            job->timer = 1;
        if ((unsigned int)previous <= 9) {
            percentage = frame_read_parameter_percentage(
                g_attachment_job_87_world.parameters, 2);
            frame_set_attachment_parameter_indicator(read_indicator(owner), percentage);
            frame_update_attachment_parameter(g_attachment_job_87_world.parameters, 2,
                read_indicator(owner));
            current = frame_read_signed_parameter(g_attachment_job_87_world.parameters, 2);
            if (current == previous + 1) {
                frame_commit_need_effect(owner->object, 1);
                owner->parameter = 0x2800;
                job->timer = 1;
            }
        } else if (previous == 10) {
            if (decrement_countdown(job->actor) == 0xFFFF) {
                frame_commit_need_effect(owner->object, 1);
                owner->parameter = 0x2800;
                job->timer = 1;
            }
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
