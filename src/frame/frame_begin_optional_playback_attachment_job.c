#include "frame_optional_playback.h"
unsigned int frame_begin_optional_playback_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *object,unsigned int kind)
{
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record(owner,object);
 unsigned int result;
 if(job){
  job->kind=kind;
  if(kind==62)frame_route_attachment_to_target(g_frame_registration,job,owner);
  else{
   struct FramePoint point;
   frame_attachment_position(owner->object,0,&point);
   frame_begin_actor_route(object,&point,&job->status,3,1);
  }
  frame_request_animation((struct FrameCommandObject *)object,6);
  result=1;
 }else result=0;
 return result;
}
asm(".align 2, 0");
