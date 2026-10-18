#include "frame_actor_attachment_counter_choices.h"

unsigned int frame_begin_counter_attachment_choices(struct FrameNeedEffectState *owner,
                                                     struct FrameObject *actor,unsigned int kind)
{
    struct FrameActorAttachmentRecord *job = frame_allocate_actor_attachment_record(
        owner,actor);
    unsigned int result;
    if (!job) result = 0;
    else {
        job->kind = kind;
        result = 1;
    }
    return result;
}
asm(".align 2,0");
