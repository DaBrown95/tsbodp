#include "display_need_effect_lifecycle.h"

void frame_detach_need_effect_actors_unrooted_2f400(
    struct FrameNeedEffectState *state)
{
    unsigned char index = 0;
    do {
        struct FrameObject *actor = state->records[index].actor;
        if (actor)
            frame_detach_actor(actor, (struct FrameObject *)state);
        index++;
    } while (index <= 2);
}
asm(".align 2, 0");
