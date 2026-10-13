#include "frame_optional_playback.h"
unsigned int frame_dispatch_optional_playback_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *object)
{
 struct FrameActorAttachmentRecord *job=frame_find_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,object);
 unsigned int result;
 switch(job->kind){
 case 57:result=frame_step_optional_playback_job_56_57(owner,job,0);break;
 case 56:result=frame_step_optional_playback_job_56_57(owner,job,1);break;
 case 1:result=frame_step_optional_playback_job_1_6(owner,job,0);break;
 case 6:result=frame_step_optional_playback_job_1_6(owner,job,1);break;
 case 62:result=frame_step_optional_playback_job_62(owner,job);break;
 case 45:result=frame_step_optional_playback_job_45(owner,job);break;
 default:result=0;break;
 }
 return result;
}
asm(".align 2, 0");
