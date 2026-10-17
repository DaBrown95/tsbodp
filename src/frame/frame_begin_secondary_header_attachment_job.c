#include "frame_need_effect_secondary_header_jobs.h"
unsigned int frame_begin_secondary_header_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 struct FramePoint point;
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record(owner,actor);
 if(job){
  unsigned char attachment;
  job->kind=kind;
  if(kind==50){
   ((struct FrameSecondaryHeaderOwnerWork *)owner)->active=1;
   if(owner->kind==53||owner->kind==51){
    struct FrameActorAttachmentRecord *first=frame_need_effect_nth_attachment(owner,1);
    unsigned char mode=frame_actor_header_mode(actor);
    attachment=100;
    if(first)attachment=((unsigned char *)&first->unknown14)[0];
    if(mode&&attachment!=3)attachment=3;
    else attachment=0;
   }else attachment=0;
   ((unsigned char *)&job->unknown14)[0]=attachment;
  }else attachment=2;
  frame_attachment_position(owner->object,attachment,&point);
  ((struct FrameSecondaryHeaderOwnerWork *)owner)->saved_position=((struct FrameActorObject *)actor)->position;
  frame_begin_actor_route(actor,&point,&job->status,0,1);
  frame_request_animation((struct FrameCommandObject *)actor,6);
  return 1;
 }
 return 0;
}
