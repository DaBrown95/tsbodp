#include "frame_actor_attachment_jobs_64_66.h"

static inline struct ConditionActorEntries *read_collection(void)
{
    return g_resource_game_state.actor.secondary_entries;
}

unsigned int frame_step_attachment_job_66(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor,
            g_actor_reverse_directions[owner->object->unknown_12[0]]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        job->timer = 7;
        break;
    case 7:
        if (job->actor->flags & 0x400000)
            job->timer = 1;
        break;
    case 1:
        {
            unsigned int added;
            if (*(short *)&owner->parameter > 0x4FFF)
                added = (unsigned char)actor_entry_add(read_collection(), 144, 0, 0);
            else
                added = (unsigned char)actor_entry_add(read_collection(), 143, 0, 0);
            if (added == 0)
                g_attachment_parameter_ui[g_input_config.local_player].flags |= 0x200000;
            else {
                if (*(short *)&owner->parameter > 0x4FFF)
                    resource_set_triple(3, 1, 1);
                owner->optional = 0;
                owner->parameter = 0;
            }
        }
        frame_commit_need_effect(owner->object, 0);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
