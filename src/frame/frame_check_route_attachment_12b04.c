#include "frame_route_attachment_21_45.h"

unsigned int frame_check_route_attachment_12b04(struct FrameNeedEffectState *owner,
                                           struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    return 1;
}
asm(".align 2, 0");
