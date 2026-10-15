#include "frame_actor_attachment_jobs_42_94.h"
unsigned int frame_dispatch_attachment_jobs_42_94(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 unsigned int result;
 switch(job->kind) {
 case 42: result=frame_step_attachment_job_42(owner,job); break;
 case 94: result=frame_step_attachment_job_94(owner,job); break;
 default: result=0;
 }
 return result;
}
