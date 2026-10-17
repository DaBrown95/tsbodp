#include "display_actor_interaction.h"

static inline struct FrameActorAttachmentRecord *attachment_record(
    struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
    unsigned char i;
    for (i = 0; i < 3; i++)
        if (owner->records[i].actor == actor) return &owner->records[i];
    return 0;
}
unsigned char frame_release_actor_attachment_record(struct FrameNeedEffectState *owner,
                                                    struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *record = attachment_record(owner, actor);
    unsigned char result;
    if (record) {
        record->actor = 0;
        record->timer = 94;
        result = 1;
    } else result = 0;
    return result;
}
asm(".align 2, 0");
