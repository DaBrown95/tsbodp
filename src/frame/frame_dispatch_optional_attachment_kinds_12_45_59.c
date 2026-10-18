#include "frame_optional_attachment_jobs_12_45_59.h"

unsigned int frame_dispatch_optional_attachment_kinds_12_45_59(
    struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job =
        frame_find_actor_attachment_record(owner, actor);
    switch ((enum FrameOptionalAttachmentKind12_45_59)job->kind) {
    case FRAME_OPTIONAL_ATTACHMENT_KIND_59:
        return frame_step_optional_attachment_kind_59(owner, job);
    case FRAME_OPTIONAL_ATTACHMENT_KIND_12:
        return frame_step_optional_attachment_kind_12_45fb4(owner, job);
    case FRAME_OPTIONAL_ATTACHMENT_KIND_45:
        return frame_step_optional_attachment_kind_45_46050(owner, job);
    }
    return 0;
}
asm(".align 2, 0");
