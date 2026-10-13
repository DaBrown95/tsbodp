#include "frame_actor_attachment_jobs.h"
unsigned int frame_dispatch_attachment_job_73(struct FrameNeedEffectState *owner,struct FrameObject *actor)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 unsigned int result;
 if(job->timer==0)frame_set_actor_direction(job->actor,frame_direction_to_need_effect_center(job->actor,owner));
 if(job->kind==73)result=frame_step_attachment_job_73(owner,job);
 else result=0;
 return result;
}
asm(".align 2, 0");
