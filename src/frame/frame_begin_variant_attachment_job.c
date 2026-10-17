#include "frame_actor_attachment_jobs.h"
unsigned int frame_begin_variant_attachment_job(struct FrameNeedEffectState *owner,struct FrameObject *actor,unsigned int kind)
{
 unsigned int variant=owner->unknown_58[6];
 struct FrameActorAttachmentRecord *job=frame_allocate_actor_attachment_record(owner,actor);
 struct FramePoint point;
 unsigned char result;
 if(job) {
  struct FrameAttachmentRouteVariant *row;
  job->kind=kind;
  {unsigned int address=(unsigned int)g_frame_attachment_route_variants;address+=variant*32;row=(struct FrameAttachmentRouteVariant *)address;}
  if(row->attachment<0)frame_route_attachment_to_target(g_frame_registration,job,owner);
  else {
   ((struct FrameAttachmentSavedPosition *)owner)->position=actor->position;
   frame_attachment_position(owner->object,row->attachment,&point);
   frame_begin_actor_route(actor,&point,&job->status,5,1);
   frame_request_animation((struct FrameCommandObject *)actor,6);
  }
  result=1;
 }else result=0;
 return result;
}

asm(".align 2, 0");
