#include "display_actor_interaction.h"

unsigned char frame_attachment_need_is_low(struct FrameActorNeedState *needs, unsigned int kind)
{
    unsigned char result = 0;
    if (kind == 8) {
        if (frame_actor_need_average(needs) <= 29) result = 1;
    } else {
        if (frame_actor_need_average(needs) <= 29 && frame_actor_need_value(needs, kind) > 30)
            result = 1;
    }
    return result;
}
asm(".align 2, 0");
