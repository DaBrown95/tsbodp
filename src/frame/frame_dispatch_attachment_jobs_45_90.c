#include "frame_actor_attachment_jobs_45_90.h"
enum FrameAttachmentJobKind45_90 {
    FRAME_ATTACHMENT_JOB_NONE = 0,
    FRAME_ATTACHMENT_JOB_45 = 45,
    FRAME_ATTACHMENT_JOB_90 = 90
};

unsigned int frame_dispatch_attachment_jobs_45_90(struct FrameNeedEffectState *owner,
                                                 struct FrameObject *actor)
{
    unsigned int result = 1;
    struct FrameActorAttachmentRecord *job = frame_find_actor_attachment_record(
        owner, actor);
    switch ((enum FrameAttachmentJobKind45_90)job->kind) {
    case 0:
        break;
    case 45:
    case 90:
        result = frame_step_attachment_jobs_45_90(owner, job);
        break;
    default:
        result = 0;
    }
    return result;
}
