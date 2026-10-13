#include "frame_optional_choice_apply.h"

void frame_optional_choice_apply(unsigned char kind,
                                 struct FrameActorAttachmentRecord *job)
{
    int cost = g_optional_choice_costs[g_optional_choice_world.stage][kind];

    if (frame_read_game_value() >= cost) {
        frame_optional_choice_install_value(kind);
        job->timer = 19;
        frame_request_animation((struct FrameCommandObject *)job->actor, 31);
    } else {
        frame_optional_choice_apply_failure();
        g_optional_choice_selection = 4;
        job->timer = 18;
        frame_request_animation((struct FrameCommandObject *)job->actor, 30);
    }
}
