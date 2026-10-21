#include "frame_optional_attachment_dispatch.h"
#include "display_actor_interaction.h"

unsigned int frame_begin_optional_direction_attachment_28880(struct FrameNeedEffectState *owner,
    struct FrameObject *actor, unsigned int kind)
{
    struct FrameActorAttachmentRecord *job =
        frame_allocate_actor_attachment_record(owner, actor);
    unsigned char direction;

    if (job) {
        job->kind = kind;
        direction = frame_direction_toward(job->actor, owner->object);
        frame_set_actor_direction(job->actor, direction);
        return 1;
    } else
        return 0;
}
asm(".align 2, 0");
