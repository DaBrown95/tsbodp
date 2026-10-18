#include "frame_actor_attachment_counter_choices.h"

unsigned int frame_step_counter_attachment_jobs_68_69(struct FrameNeedEffectState *owner,
                                                      struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        {
            struct FrameActorSceneState *world;
            if (g_resource_game_state.scene.variant == 0)
                frame_add_game_value(-100);
            else frame_settle_actor_scene_counter(1);
            world = &g_resource_game_state.scene;
            world->timer = -2;
            job->timer = 1;
            g_scene_mode_bytes[0] = 8;
            resource_submit_scene(1,0,12);
            audio_play_animation_cue(40);
        }
        break;
    case 1:
        frame_request_animation((struct FrameCommandObject *)job->actor,1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2,0");
