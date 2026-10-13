#include "frame_need_effect_optional_activity.h"
#include "display_need_effect_update.h"

unsigned char frame_need_effect_try_reset_timer(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor)
{
    unsigned char ready;
    if (owner->enabled && g_need_effect_player == actor)
        ready = frame_random_chance(15 - frame_read_signed_parameter(g_frame_actor_social_probe, 0));
    else
        ready = 0;
    if (ready == 1)
        ((struct DisplayNeedEffectActorView *)owner->object)->timer = 0;
    return ready;
}
