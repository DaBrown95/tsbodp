#include "display_need_effect_lifecycle.h"

unsigned int frame_check_attachment_capacity_unrooted_461c8(
    struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    if (frame_need_effect_attachment_count(owner) >= owner->unknown_58[5])
        return 0;
    return 1;
}
asm(".align 2, 0");
