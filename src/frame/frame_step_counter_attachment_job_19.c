#include "frame_actor_attachment_counter_choices.h"

unsigned int frame_step_counter_attachment_job_19(struct FrameNeedEffectState *owner,
                                                  struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        if (g_need_effect_choice_state.index != -1) {
            job->timer = 1;
            frame_remove_counter_attachment_selection();
            frame_present_counter_attachment_choice();
        }
        break;
    case 1:
        {
            struct FrameActorSceneState *world;
            frame_request_animation((struct FrameCommandObject *)job->actor,1);
            result = 2;
            world = &g_resource_game_state.scene;
            world->timer = -2;
            world->counter.value = 0;
            g_scene_mode_bytes[0] = 8;
            resource_submit_scene(1,0,12);
        }
        break;
    }
    return result;
}
asm(".align 2,0");
