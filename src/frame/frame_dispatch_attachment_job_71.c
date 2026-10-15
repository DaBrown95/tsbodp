#include "frame_actor_attachment_job_71.h"
unsigned int frame_dispatch_attachment_job_71(struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 unsigned int result;
 if(job->kind==71)result=frame_step_attachment_job_71(owner,job);
 else result=0;
 return result;
}
