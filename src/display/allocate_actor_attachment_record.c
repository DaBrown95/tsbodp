#include "display_actor_interaction.h"

struct FrameActorAttachmentRecord *frame_allocate_actor_attachment_record(
    struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
    unsigned char i;
    for (i = 0; i < 3; i++) {
        if (!owner->records[i].actor) {
            owner->records[i].actor = actor;
            owner->records[i].timer = 0;
            owner->records[i].kind = 0;
            owner->records[i].running = 0;
            owner->records[i].status = 0;
            *(unsigned char *)&owner->records[i].unknown14 = 0;
            return &owner->records[i];
        }
    }
    return 0;
}
asm(".align 2, 0");
