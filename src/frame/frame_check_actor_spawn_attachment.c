#include "frame_actor_spawn_attachment.h"

unsigned int frame_check_actor_spawn_attachment(struct FrameNeedEffectState *owner,
                                               struct FrameObject *actor)
{
    if (frame_count_actor_attachments(actor) && owner->unknown_60[0] == 1)
        return 0;
    if ((short)owner->parameter == 1)
        return 0;
    return 1;
}
asm(".align 2, 0");
