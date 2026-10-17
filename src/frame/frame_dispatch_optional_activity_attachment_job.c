#include "frame_need_effect_optional_activity.h"

unsigned int frame_dispatch_optional_activity_attachment_job(struct FrameNeedEffectState *owner,
                                                               struct FrameObject *actor)
{
    struct FrameActorAttachmentRecord *job =
        frame_find_actor_attachment_record(owner, actor);
    switch (job->kind) {
    case 28: case 30: case 31: case 32:
        return frame_step_optional_activity_attachment_job(owner, job);
    case 12:
        return frame_step_optional_attachment_kind_12(owner, job);
    case 45:
        return frame_step_optional_attachment_kind_45(owner, job);
    case 22:
        return frame_step_optional_attachment_kind_22(owner, job);
    }
    return 0;
}
