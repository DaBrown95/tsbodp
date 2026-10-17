#include "display_actor_interaction.h"

struct FrameActorAttachmentRecord *frame_find_actor_attachment_record(
    struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
    unsigned char i;
    for (i = 0; i < 3; i++)
        if (owner->records[i].actor == actor) return &owner->records[i];
    return 0;
}
