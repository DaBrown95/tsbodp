#include "frame_need_effect_secondary_header_jobs.h"
unsigned int frame_step_secondary_header_attachment_job_27(struct FrameNeedEffectState *owner,struct FrameActorAttachmentRecord *job)
{
 unsigned int result=1;
 if(job->running==1)job->timer=1;
 switch((unsigned int)job->timer){
 case 0:
  owner->parameter=0;
  owner->optional=0;
  ((struct FrameActorObject *)job->actor)->direction=g_secondary_header_attachment_directions_one[((struct FrameActorObject *)owner->object)->direction];
  frame_request_animation((struct FrameCommandObject *)job->actor,10);
  ((struct FrameActorStateWork *)job->actor)->timer=14;
  job->timer=9;
  break;
 case 9:
  if(job->actor->flags&0x400000){
   frame_request_animation((struct FrameCommandObject *)job->actor,6);
   frame_commit_need_effect(owner->object,1);
   job->timer=1;
  }
  break;
 case 1:
  frame_request_animation((struct FrameCommandObject *)job->actor,1);
  result=2;
  break;
 }
 return result;
}
