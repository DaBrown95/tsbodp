#include "frame_need_effect_condition_jobs.h"
#include "frame_need_effect_optional_jobs.h"
#include "resource_conditions.h"
#include "frame_actor_social.h"
unsigned int frame_step_condition_wait_job(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 if (job->running==1) job->timer=1;
 switch ((unsigned int)job->timer) {
 case 0:
  if (((struct FrameActorObject *)owner->object)->direction<=4)
   frame_set_actor_direction(job->actor,2);
  else
   frame_set_actor_direction(job->actor,6);
  frame_request_animation((struct FrameCommandObject *)job->actor,28);
  job->timer=71;
  ((struct FrameActorActionWork *)job->actor)->timer=180;
  break;
 case 71: {
  struct FrameActorActionWork *work=(struct FrameActorActionWork *)job->actor;
  work->timer=(int)((unsigned int)work->timer-1u);
  if (work->timer==-1) {
   job->timer=1;
   condition_complete_if_active(1,4,1);
  }
  break;
 }
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 return result;
}
asm(".align 2, 0");
