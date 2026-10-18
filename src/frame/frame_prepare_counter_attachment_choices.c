#include "frame_actor_attachment_counter_choices.h"

unsigned int frame_prepare_counter_attachment_choices(struct FrameNeedEffectState *owner,
                                                       struct FrameObject *actor,
                                                       unsigned int kind)
{
    union ResourceGameState *world = &g_resource_game_state;
    switch (world->scene.variant) {
    case 1:
        if (world->actor_values.value == 0) {
            if (kind == 19) goto accept;
        } else {
            if (kind == 68) goto accept;
        }
        goto reject;
    case 0:
        if (world->actor_values.value <= 99 && kind == 69) goto reject;
        break;
    }
    goto accept;
reject:
    return 0;
accept:
    return 1;
}
asm(".align 2,0");
