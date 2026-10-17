#include "frame_actor_attachment_job_48.h"
unsigned int frame_dispatch_attachment_job_48(struct FrameNeedEffectState *owner, struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record(owner,actor);
 unsigned int result;
 if(job->kind==48)result=frame_step_attachment_job_48(owner,job);
 else result=0;
 return result;
}
