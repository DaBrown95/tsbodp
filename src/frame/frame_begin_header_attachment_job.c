#include "frame_need_effect_header_jobs.h"
#include "display_actor_interaction.h"
#include "frame_need_effect_header_choices.h"
unsigned int frame_begin_header_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 struct FramePoint point;
 struct FrameActorAttachmentRecord *first=frame_need_effect_nth_attachment((struct FrameActorAttachmentOwner *)owner,1);
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record((struct FrameActorAttachmentOwner *)owner,actor);
 if(job){
  unsigned char mode,attachment;
  job->kind=kind;
  mode=frame_actor_header_mode(actor);
  attachment=100;
  if(first)attachment=((unsigned char *)&first->unknown14)[0];
  if(kind==50)attachment=0;
  else if(kind==49){
   if(!mode||attachment==1)attachment=2;
   else attachment=1;
   ((unsigned char *)&job->unknown14)[0]=attachment;
  }else return 0;
  frame_attachment_position(owner->object,attachment,&point);
  frame_begin_actor_route(actor,&point,&job->status,3,0);
  frame_request_animation((struct FrameCommandObject *)actor,6);
  return 1;
 }
 return 0;
}
asm(".align 2, 0");
