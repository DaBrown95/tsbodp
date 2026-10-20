#include "frame_optional_routes_12_23_60.h"

unsigned int frame_step_optional_route_kind_12(struct FrameNeedEffectState *owner,
                                               struct FrameActorAttachmentRecord *job)
{
    unsigned int result = 1;
    if (job->running == 1) job->timer = 1;
    switch ((unsigned int)job->timer) {
    case 0:
        frame_request_animation((struct FrameCommandObject *)job->actor, 14);
        job->timer = 4;
        owner->optional_sample = audio_play_animation_cue(26);
        break;
    case 4: {
        struct FrameActorNeedState *needs = ((struct FrameActorObject *)job->actor)->actor_state;
        frame_adjust_actor_needs(needs, 52, g_frame_need_effect_definitions[owner->kind].unknown_04[31]);
        if ((unsigned char)frame_need_effect_consume_optional_two(owner) == 1)
            job->timer = 1;
        break;
    }
    case 1:
        audio_game_stop_sample(owner->optional_sample);
        frame_request_animation((struct FrameCommandObject *)job->actor, 1);
        result = 2;
        break;
    }
    return result;
}
asm(".align 2,0");
