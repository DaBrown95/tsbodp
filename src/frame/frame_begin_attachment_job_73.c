#include "frame_actor_attachment_jobs.h"
unsigned int frame_begin_attachment_job_73(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 unsigned char result;
 if(!job)result=0;
 else {
  job->kind=kind;
  frame_route_attachment_to_target(g_frame_registration,job,owner);
  frame_request_animation((struct FrameCommandObject *)actor,6);
  ((struct FrameActorStateWork *)job->actor)->timer=60;
  result=1;
 }
 return result;
}
