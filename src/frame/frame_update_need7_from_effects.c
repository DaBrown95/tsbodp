#include "frame_need_effect_average.h"

void frame_update_need7_from_effects(void)
{
    struct FrameActorNeedState *needs =
        (struct FrameActorNeedState *)g_frame_actor_local_need_state;
    if (frame_world_in_idle_exclusion_set(g_frame_world_id) == 1 ||
        g_frame_world_id == 28) {
        unsigned char count;
        unsigned char target = frame_need_effect_average(&count);
        unsigned char current = frame_actor_need_value(needs, 7);
        if (!count)
            target = 25;
        if (current < target)
            frame_adjust_actor_needs(needs, 41, 1);
        else if (current > target)
            frame_adjust_actor_needs(needs, 43, 1);
    } else {
        frame_adjust_actor_needs(needs, 42, 1);
    }
}

asm(".align 2, 0");
