#include "display_actor_interaction.h"

unsigned char frame_interaction_can_begin_31(struct FrameNeedEffectState *owner,
                                             struct FrameObject *object)
{
    if (frame_count_actor_attachments(object) && owner->unknown_60[0] == 1) return 0;
    return 1;
}
asm(".align 2, 0");
