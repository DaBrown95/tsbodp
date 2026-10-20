#include "frame_actor_attachment_job_68.h"

unsigned int frame_step_attachment_job_68(struct FrameNeedEffectState *owner,
                                          struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1)
        job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_set_actor_direction(job->actor, g_actor_reverse_directions[
            ((struct FrameActorObject *)owner->object)->direction]);
        frame_request_animation((struct FrameCommandObject *)job->actor, 58);
        frame_commit_need_effect(owner->object, 1);
        audio_play_animation_cue(60u);
        job->timer = 78;
        break;
    case 78:
        if (g_resource_game_state.actor_values.value == 0 &&
                g_resource_game_state.scene.counter != 0) {
            job->timer = 1;
            g_actor_scene_result_id.id = 0x125;
            frame_activate_actor_scene_request();
            break;
        }
        if (job->actor->flags & 0x400000) {
            audio_play_animation_cue(5);
            job->timer = 79;
            ((struct FrameActorObject *)job->actor)->need_timer = 150;
        }
        if (g_need_effect_choice_state.index != -1)
            frame_settle_actor_scene_counter(0);
        break;
    case 79:
        frame_commit_need_effect(owner->object, 2);
        job->timer = 1;
        break;
    case 1:
        audio_play_animation_cue(60);
        frame_commit_need_effect(owner->object, 0);
        frame_set_animation_frame((struct FrameTickObject *)owner->object,
            g_resource_game_state.scene.counter != 0);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
