#include "frame_need_effect.h"
#include "frame_actor_social.h"
#include "resource_conditions.h"

unsigned int frame_select_need_actions_17ac4(struct FrameNeedEffectState *state,
                                            unsigned char *out)
{
    unsigned int count = 0;
    if (*(short *)&state->parameter > 0) {
        *out = 66;
    } else if ((unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 2) > 3 &&
               (((unsigned char)condition_is_active(3, 1, 1) == 1 &&
                 (unsigned char)condition_is_complete(3, 1, 1) == 0) ||
                ((unsigned char)condition_is_complete(3, 1, 1) == 1 &&
                 (unsigned int)frame_read_signed_parameter(g_frame_actor_social_probe, 2) > 6))) {
        out = (unsigned char *)((unsigned int)out | count);
        *out = 65;
    } else {
        out = (unsigned char *)((unsigned int)out | count);
        *out = 64;
    }
    return 1;
}

asm(".align 2, 0");
